#ifndef GIT_UTILS_H
#define GIT_UTILS_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool git_is_repository(const char *directory);

bool git_clone(const char *url,
               const char *directory);

bool git_pull(const char *directory);

bool git_checkout(const char *directory,
                  const char *branch);

bool git_clone_or_pull(const char *url,
                       const char *directory);

bool git_update_submodules(const char *directory);

#ifdef __cplusplus
}
#endif

#endif
