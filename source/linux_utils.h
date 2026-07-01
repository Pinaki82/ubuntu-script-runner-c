#ifndef LINUX_UTILS_H
#define LINUX_UTILS_H

#if !(defined(__gnu_linux__) || defined(_POSIX_VERSION))
  #error "linux_utils is intended for POSIX/Linux systems only."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
   Path utilities
   ------------------------------------------------------------------------- */

char *expand_home(const char *path);

char *join_path(const char *left,
                const char *right);

int ensure_parent_directory(const char *path);

int mkdir_p(const char *path,
            mode_t mode);

/* -------------------------------------------------------------------------
   File type tests
   ------------------------------------------------------------------------- */

bool path_exists(const char *path);

bool file_exists(const char *path);

bool directory_exists(const char *path);

bool is_regular_file(const char *path);

bool is_directory(const char *path);

bool is_symlink(const char *path);

/* -------------------------------------------------------------------------
   File operations
   ------------------------------------------------------------------------- */

int copy_file(const char *source,
              const char *destination);

int move_file(const char *source,
              const char *destination);

int remove_file(const char *path);

int remove_directory_recursive(const char *path);

int copy_directory_recursive(const char *source,
                             const char *destination);

/* -------------------------------------------------------------------------
   Symbolic links
   ------------------------------------------------------------------------- */

int create_symlink_force(const char *target,
                         const char *linkpath);

int read_symlink(const char *path,
                 char *buffer,
                 size_t buffer_size);

/* -------------------------------------------------------------------------
   Backup helpers
   ------------------------------------------------------------------------- */

int backup_existing(const char *path);

int backup_existing_to(const char *path,
                       const char *backup_root);

/* -------------------------------------------------------------------------
   Directory traversal
   ------------------------------------------------------------------------- */

int directory_is_empty(const char *path);

#ifdef __cplusplus
}
#endif

#endif /* LINUX_UTILS_H */
