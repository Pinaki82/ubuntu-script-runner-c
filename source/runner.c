#include "runner.h"

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>

static runner_result runner_execute(const char *cwd,
                                    char *const argv[]) {
  runner_result result = {
    .exit_code = -1,
    .success = false
  };
  pid_t pid = fork();

  if(pid < 0) {
    return result;
  }

  if(pid == 0) {
    if(cwd != NULL) {
      if(chdir(cwd) != 0) {
        _exit(errno);
      }
    }

    execvp(argv[0], argv);
    _exit(errno);
  }

  int status = 0;

  if(waitpid(pid, &status, 0) < 0) {
    return result;
  }

  if(WIFEXITED(status)) {
    result.exit_code = WEXITSTATUS(status);
    result.success = (result.exit_code == 0);
  }

  return result;
}

runner_result runner_run(char *const argv[]) {
  return runner_execute(NULL, argv);
}

runner_result runner_run_in(const char *working_directory,
                            char *const argv[]) {
  return runner_execute(working_directory,
                        argv);
}

runner_result runner_shell(const char *command) {
  char *const argv[] = {
    "sh",
    "-c",
    (char *)command,
    NULL
  };
  return runner_run(argv);
}

runner_result runner_shell_in(const char *working_directory,
                              const char *command) {
  char *const argv[] = {
    "sh",
    "-c",
    (char *)command,
    NULL
  };
  return runner_run_in(working_directory,
                       argv);
}

bool runner_command_exists(const char *command) {
  char *path = getenv("PATH");

  if(path == NULL) {
    return false;
  }

  char *copy = strdup(path);

  if(copy == NULL) {
    return false;
  }

  bool found = false;

  for(char *dir = strtok(copy, ":");
      dir != NULL;
      dir = strtok(NULL, ":")) {
    char filename[PATH_MAX];
    snprintf(filename,
             sizeof(filename),
             "%s/%s",
             dir,
             command);

    if(access(filename, X_OK) == 0) {
      found = true;
      break;
    }
  }

  free(copy);
  return found;
}
