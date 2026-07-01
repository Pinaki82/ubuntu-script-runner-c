#include "git_utils.h"
#include "runner.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

bool git_is_repository(const char *directory) {
  char gitdir[PATH_MAX];
  snprintf(gitdir,
           sizeof(gitdir),
           "%s/.git",
           directory);
  return access(gitdir, F_OK) == 0;
}

bool git_clone(const char *url,
               const char *directory) {
  char *const argv[] = {
    "git",
    "clone",
    "--depth",
    "1",
    (char *)url,
    (char *)directory,
    NULL
  };
  return runner_run(argv).success;
}

bool git_pull(const char *directory) {
  char *const argv[] = {
    "git",
    "pull",
    "--ff-only",
    NULL
  };
  return runner_run_in(directory,
                       argv).success;
}

bool git_checkout(const char *directory,
                  const char *branch) {
  char *const argv[] = {
    "git",
    "checkout",
    (char *)branch,
    NULL
  };
  return runner_run_in(directory,
                       argv).success;
}

bool git_update_submodules(const char *directory) {
  char *const argv[] = {
    "git",
    "submodule",
    "update",
    "--init",
    "--recursive",
    NULL
  };
  return runner_run_in(directory,
                       argv).success;
}

bool git_clone_or_pull(const char *url,
                       const char *directory) {
  if(git_is_repository(directory)) {
    return git_pull(directory);
  }

  return git_clone(url,
                   directory);
}
