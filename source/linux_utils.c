// linux_utils.c
//
// Part 1
// Path utilities and file type helpers.

#include "linux_utils.h"

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/* ------------------------------------------------------------------------- */
/* Internal helpers                                                          */
/* ------------------------------------------------------------------------- */

static bool stat_path(const char *path, struct stat *st) {
  if(path == NULL) {
    return false;
  }

  return stat(path, st) == 0;
}

static bool lstat_path(const char *path, struct stat *st) {
  if(path == NULL) {
    return false;
  }

  return lstat(path, st) == 0;
}

/* ------------------------------------------------------------------------- */
/* Path utilities                                                            */
/* ------------------------------------------------------------------------- */

char *expand_home(const char *path) {
  if(path == NULL) {
    return NULL;
  }

  if(path[0] != '~') {
    return strdup(path);
  }

  const char *home = getenv("HOME");

  if(home == NULL) {
    return NULL;
  }

  size_t home_len = strlen(home);
  size_t path_len = strlen(path);
  char *expanded = malloc(home_len + path_len + 1);

  if(expanded == NULL) {
    return NULL;
  }

  strcpy(expanded, home);
  strcat(expanded, path + 1);
  return expanded;
}

char *join_path(const char *left,
                const char *right) {
  if(left == NULL || right == NULL) {
    return NULL;
  }

  size_t left_len  = strlen(left);
  size_t right_len = strlen(right);
  bool need_slash =
          (left_len > 0) &&
          (left[left_len - 1] != '/');
  char *result =
          malloc(left_len + right_len + (need_slash ? 2 : 1));

  if(result == NULL) {
    return NULL;
  }

  strcpy(result, left);

  if(need_slash) {
    strcat(result, "/");
  }

  strcat(result, right);
  return result;
}

/* ------------------------------------------------------------------------- */
/* Existence tests                                                           */
/* ------------------------------------------------------------------------- */

bool path_exists(const char *path) {
  struct stat st;
  return stat_path(path, &st);
}

bool file_exists(const char *path) {
  struct stat st;

  if(!stat_path(path, &st)) {
    return false;
  }

  return S_ISREG(st.st_mode);
}

bool directory_exists(const char *path) {
  struct stat st;

  if(!stat_path(path, &st)) {
    return false;
  }

  return S_ISDIR(st.st_mode);
}

bool is_regular_file(const char *path) {
  struct stat st;

  if(!stat_path(path, &st)) {
    return false;
  }

  return S_ISREG(st.st_mode);
}

bool is_directory(const char *path) {
  struct stat st;

  if(!stat_path(path, &st)) {
    return false;
  }

  return S_ISDIR(st.st_mode);
}

bool is_symlink(const char *path) {
  struct stat st;

  if(!lstat_path(path, &st)) {
    return false;
  }

  return S_ISLNK(st.st_mode);
}

/* ------------------------------------------------------------------------- */
/* Directory creation                                                        */
/* ------------------------------------------------------------------------- */

int mkdir_p(const char *path, mode_t mode) {
  if(path == NULL || *path == '\0') {
    errno = EINVAL;
    return -1;
  }

  char *tmp = strdup(path);

  if(tmp == NULL) {
    return -1;
  }

  size_t len = strlen(tmp);

  /* Remove trailing '/' (except for root "/") */
  while(len > 1 && tmp[len - 1] == '/') {
    tmp[--len] = '\0';
  }

  for(char *p = tmp + 1; *p != '\0'; ++p) {
    if(*p != '/') {
      continue;
    }

    *p = '\0';

    if(mkdir(tmp, mode) != 0) {
      if(errno != EEXIST) {
        int saved = errno;
        free(tmp);
        errno = saved;
        return -1;
      }

      struct stat st;

      if(stat(tmp, &st) != 0 || !S_ISDIR(st.st_mode)) {
        free(tmp);
        errno = ENOTDIR;
        return -1;
      }
    }

    *p = '/';
  }

  if(mkdir(tmp, mode) != 0) {
    if(errno != EEXIST) {
      int saved = errno;
      free(tmp);
      errno = saved;
      return -1;
    }

    struct stat st;

    if(stat(tmp, &st) != 0 || !S_ISDIR(st.st_mode)) {
      free(tmp);
      errno = ENOTDIR;
      return -1;
    }
  }

  free(tmp);
  return 0;
}

/* ------------------------------------------------------------------------- */

int ensure_parent_directory(const char *path) {
  if(path == NULL) {
    errno = EINVAL;
    return -1;
  }

  char *copy = strdup(path);

  if(copy == NULL) {
    return -1;
  }

  char *slash = strrchr(copy, '/');

  if(slash == NULL) {
    free(copy);
    return 0;
  }

  /*
     "/file"
  */
  if(slash == copy) {
    slash[1] = '\0';
    free(copy);
    return 0;
  }

  *slash = '\0';
  int rc = mkdir_p(copy, 0755);
  int saved = errno;
  free(copy);
  errno = saved;
  return rc;
}

/* ------------------------------------------------------------------------- */
/* File operations                                                           */
/* ------------------------------------------------------------------------- */

int copy_file(const char *source,
              const char *destination) {
  if(source == NULL || destination == NULL) {
    errno = EINVAL;
    return -1;
  }

  if(ensure_parent_directory(destination) != 0) {
    return -1;
  }

  FILE *src = fopen(source, "rb");

  if(src == NULL) {
    return -1;
  }

  FILE *dst = fopen(destination, "wb");

  if(dst == NULL) {
    int saved = errno;
    fclose(src);
    errno = saved;
    return -1;
  }

  char buffer[8192];

  while(1) {
    size_t bytes = fread(buffer, 1, sizeof(buffer), src);

    if(bytes > 0) {
      if(fwrite(buffer, 1, bytes, dst) != bytes) {
        int saved = errno;
        fclose(src);
        fclose(dst);
        remove(destination);
        errno = saved;
        return -1;
      }
    }

    if(bytes < sizeof(buffer)) {
      if(ferror(src)) {
        int saved = errno;
        fclose(src);
        fclose(dst);
        remove(destination);
        errno = saved;
        return -1;
      }

      break;
    }
  }

  fclose(src);

  if(fclose(dst) != 0) {
    remove(destination);
    return -1;
  }

  struct stat st;

  if(stat(source, &st) == 0) {
    chmod(destination, st.st_mode & 07777);
  }

  return 0;
}

/* ------------------------------------------------------------------------- */

int move_file(const char *source,
              const char *destination) {
  if(source == NULL || destination == NULL) {
    errno = EINVAL;
    return -1;
  }

  if(ensure_parent_directory(destination) != 0) {
    return -1;
  }

  if(rename(source, destination) == 0) {
    return 0;
  }

  if(errno != EXDEV) {
    return -1;
  }

  if(copy_file(source, destination) != 0) {
    return -1;
  }

  if(unlink(source) != 0) {
    int saved = errno;
    remove(destination);
    errno = saved;
    return -1;
  }

  return 0;
}

/* ------------------------------------------------------------------------- */

int remove_file(const char *path) {
  if(path == NULL) {
    errno = EINVAL;
    return -1;
  }

  return unlink(path);
}

#include <dirent.h>

/* ------------------------------------------------------------------------- */
/* Internal recursive copy helper                                            */
/* ------------------------------------------------------------------------- */

static int copy_directory_internal(const char *source,
                                   const char *destination) {
  DIR *dir = opendir(source);

  if(dir == NULL) {
    return -1;
  }

  struct stat st;

  if(stat(source, &st) != 0) {
    int saved = errno;
    closedir(dir);
    errno = saved;
    return -1;
  }

  if(mkdir(destination, st.st_mode & 07777) != 0) {
    if(errno != EEXIST) {
      int saved = errno;
      closedir(dir);
      errno = saved;
      return -1;
    }
  }

  struct dirent *entry;

  while((entry = readdir(dir)) != NULL) {
    if(strcmp(entry->d_name, ".") == 0) {
      continue;
    }

    if(strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char *src =
            join_path(source, entry->d_name);
    char *dst =
            join_path(destination, entry->d_name);

    if(src == NULL || dst == NULL) {
      free(src);
      free(dst);
      closedir(dir);
      errno = ENOMEM;
      return -1;
    }

    struct stat est;

    if(lstat(src, &est) != 0) {
      int saved = errno;
      free(src);
      free(dst);
      closedir(dir);
      errno = saved;
      return -1;
    }

    if(S_ISDIR(est.st_mode)) {
      if(copy_directory_internal(src, dst) != 0) {
        free(src);
        free(dst);
        closedir(dir);
        return -1;
      }
    }

    else if(S_ISREG(est.st_mode)) {
      if(copy_file(src, dst) != 0) {
        free(src);
        free(dst);
        closedir(dir);
        return -1;
      }
    }

    else if(S_ISLNK(est.st_mode)) {
      char target[PATH_MAX];
      ssize_t len =
              readlink(src,
                       target,
                       sizeof(target) - 1);

      if(len < 0) {
        int saved = errno;
        free(src);
        free(dst);
        closedir(dir);
        errno = saved;
        return -1;
      }

      target[len] = '\0';

      if(symlink(target, dst) != 0) {
        int saved = errno;
        free(src);
        free(dst);
        closedir(dir);
        errno = saved;
        return -1;
      }
    }

    free(src);
    free(dst);
  }

  closedir(dir);
  return 0;
}

/* ------------------------------------------------------------------------- */
/* Public recursive copy                                                     */
/* ------------------------------------------------------------------------- */

int copy_directory_recursive(const char *source,
                             const char *destination) {
  if(source == NULL || destination == NULL) {
    errno = EINVAL;
    return -1;
  }

  return copy_directory_internal(source,
                                 destination);
}

#include <dirent.h>

/* ------------------------------------------------------------------------- */
/* Internal recursive remove helper                                          */
/* ------------------------------------------------------------------------- */

static int remove_directory_internal(const char *path) {
  DIR *dir = opendir(path);

  if(dir == NULL) {
    return -1;
  }

  struct dirent *entry;

  while((entry = readdir(dir)) != NULL) {
    if(strcmp(entry->d_name, ".") == 0) {
      continue;
    }

    if(strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char *child = join_path(path, entry->d_name);

    if(child == NULL) {
      closedir(dir);
      errno = ENOMEM;
      return -1;
    }

    struct stat st;

    if(lstat(child, &st) != 0) {
      int saved = errno;
      free(child);
      closedir(dir);
      errno = saved;
      return -1;
    }

    if(S_ISDIR(st.st_mode)) {
      if(remove_directory_internal(child) != 0) {
        free(child);
        closedir(dir);
        return -1;
      }
    }

    else {
      if(unlink(child) != 0) {
        int saved = errno;
        free(child);
        closedir(dir);
        errno = saved;
        return -1;
      }
    }

    free(child);
  }

  closedir(dir);
  return rmdir(path);
}

/* ------------------------------------------------------------------------- */

int remove_directory_recursive(const char *path) {
  if(path == NULL) {
    errno = EINVAL;
    return -1;
  }

  return remove_directory_internal(path);
}

/* ------------------------------------------------------------------------- */

int create_symlink_force(const char *target,
                         const char *linkpath) {
  if(target == NULL || linkpath == NULL) {
    errno = EINVAL;
    return -1;
  }

  unlink(linkpath);
  ensure_parent_directory(linkpath);
  return symlink(target, linkpath);
}

/* ------------------------------------------------------------------------- */

int read_symlink(const char *path,
                 char *buffer,
                 size_t buffer_size) {
  if(path == NULL ||
     buffer == NULL ||
     buffer_size == 0) {
    errno = EINVAL;
    return -1;
  }

  ssize_t len = readlink(path,
                         buffer,
                         buffer_size - 1);

  if(len < 0) {
    return -1;
  }

  buffer[len] = '\0';
  return 0;
}

/* ------------------------------------------------------------------------- */

int backup_existing(const char *path) {
  if(!path_exists(path)) {
    return 0;
  }

  size_t len = strlen(path);
  char *backup = malloc(len + 6);

  if(backup == NULL) {
    return -1;
  }

  sprintf(backup, "%s.bak", path);
  int rc = move_file(path, backup);
  free(backup);
  return rc;
}

/* ------------------------------------------------------------------------- */

int backup_existing_to(const char *path,
                       const char *backup_root) {
  if(path == NULL || backup_root == NULL) {
    errno = EINVAL;
    return -1;
  }

  const char *name = strrchr(path, '/');
  name = (name == NULL) ? path : name + 1;
  char *backup = join_path(backup_root, name);

  if(backup == NULL) {
    errno = ENOMEM;
    return -1;
  }

  int rc = move_file(path, backup);
  free(backup);
  return rc;
}

/* ------------------------------------------------------------------------- */

int directory_is_empty(const char *path) {
  DIR *dir = opendir(path);

  if(dir == NULL) {
    return -1;
  }

  struct dirent *entry;

  while((entry = readdir(dir)) != NULL) {
    if(strcmp(entry->d_name, ".") != 0 &&
       strcmp(entry->d_name, "..") != 0) {
      closedir(dir);
      return 0;
    }
  }

  closedir(dir);
  return 1;
}
