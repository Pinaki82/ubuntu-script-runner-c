#include "dotfile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_entire_file(const char *filename) {
  FILE *fp = fopen(filename, "rb");

  if(fp == NULL) {
    return NULL;
  }

  if(fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return NULL;
  }

  long size = ftell(fp);

  if(size < 0) {
    fclose(fp);
    return NULL;
  }

  rewind(fp);
  char *buffer = malloc((size_t)size + 1);

  if(buffer == NULL) {
    fclose(fp);
    return NULL;
  }

  if(size > 0) {
    if(fread(buffer, 1, (size_t)size, fp) != (size_t)size) {
      free(buffer);
      fclose(fp);
      return NULL;
    }
  }

  buffer[size] = '\0';
  fclose(fp);
  return buffer;
}

bool dotfile_contains(const char *filename,
                      const char *text) {
  char *contents = read_entire_file(filename);

  if(contents == NULL) {
    return false;
  }

  bool found = strstr(contents, text) != NULL;
  free(contents);
  return found;
}

bool dotfile_append_if_missing(const char *filename,
                               const char *line) {
  if(dotfile_contains(filename, line)) {
    return true;
  }

  FILE *fp = fopen(filename, "a");

  if(fp == NULL) {
    return false;
  }

  fprintf(fp, "\n%s\n", line);
  fclose(fp);
  return true;
}

bool dotfile_append_block_if_missing(const char *filename,
                                     const char *begin_marker,
                                     const char *block,
                                     const char *end_marker) {
  if(dotfile_contains(filename, begin_marker)) {
    return true;
  }

  FILE *fp = fopen(filename, "a");

  if(fp == NULL) {
    return false;
  }

  fprintf(fp,
          "\n%s\n%s\n%s\n",
          begin_marker,
          block,
          end_marker);
  fclose(fp);
  return true;
}

bool dotfile_remove_block(const char *filename,
                          const char *begin_marker,
                          const char *end_marker) {
  char *contents = read_entire_file(filename);

  if(contents == NULL) {
    return false;
  }

  char *begin = strstr(contents, begin_marker);

  if(begin == NULL) {
    free(contents);
    return true;
  }

  char *end = strstr(begin, end_marker);

  if(end == NULL) {
    free(contents);
    return false;
  }

  end += strlen(end_marker);
  FILE *fp = fopen(filename, "w");

  if(fp == NULL) {
    free(contents);
    return false;
  }

  fwrite(contents, 1, (size_t)(begin - contents), fp);
  fputs(end, fp);
  fclose(fp);
  free(contents);
  return true;
}
