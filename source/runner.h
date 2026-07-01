#ifndef RUNNER_H
#define RUNNER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int exit_code;
  bool success;
} runner_result;

/*
   Execute argv.

   argv must be NULL terminated.
*/
runner_result
runner_run(char *const argv[]);

/*
   Execute argv inside working_directory.
*/
runner_result
runner_run_in(const char *working_directory,
              char *const argv[]);

/*
   Execute using /bin/sh -c.
*/
runner_result
runner_shell(const char *command);

/*
   Execute inside a working directory using /bin/sh -c.
*/
runner_result
runner_shell_in(const char *working_directory,
                const char *command);

/*
   Returns true if executable exists in PATH.
*/
bool
runner_command_exists(const char *command);

#ifdef __cplusplus
}
#endif

#endif
