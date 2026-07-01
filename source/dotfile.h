#ifndef DOTFILE_H
#define DOTFILE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool
dotfile_append_if_missing(const char *filename,
                          const char *line);

bool
dotfile_append_block_if_missing(const char *filename,
                                const char *begin_marker,
                                const char *block,
                                const char *end_marker);

bool
dotfile_contains(const char *filename,
                 const char *text);

bool
dotfile_remove_block(const char *filename,
                     const char *begin_marker,
                     const char *end_marker);

#ifdef __cplusplus
}
#endif

#endif
