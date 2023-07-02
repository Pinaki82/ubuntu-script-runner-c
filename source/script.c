// Last Change: 2023-07-03  Monday: 01:22:32 AM
// #!/usr/bin/c -Wall -Wextra -pedantic --std=c99
// Restrict to Linux systems only
#if !( defined( __gnu_linux__ ) || defined(_POSIX_VERSION) )
  #error "For UNIX-like Operating Systems Only"
#endif

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <time.h>
#include "sf_c.h"

#define VERSION "1" /* defines a constant string called "VERSION" with the value 1 */
#define NO_OF_ARGS 2 /* the exact no. of command-line arguments the program takes */

#define MAXLINELEN 2048
#define MAX_STRING_LENGTH_4_SPECIAL 100
#define PIPE_YES  "yes |"
#define SUDOCOMMAND  "sudo"

#define strndup sf_strndup
#define strncpy sf_strncpy
#define strncat sf_strncat

int home_config = 0; // global flag to check if the file is in the home (~/.config/scriptrunner) directory. 0 means the file is in the root of the program's folder

int readLineFromFile(FILE *file, int *totalLines, char ***lineContents);
void copyStringWithoutPrefix(const char *input, char *output, const char *prefix);
char *expand_tilde(const char *path);
int executeCommand(const char *command);
void package_manager(char *package_manager_name);
void install_command(char *command_2_install_apps);
int renewsys(void);
int package_installer(void);

// Function to read from a text file line by line
// Arguments:
//   file: The file pointer to read from
//   totalLines: A pointer to store the total number of lines in the file
//   lineContents: A pointer to store the contents of the requested line
// Returns:
//   0 if the function executes successfully, -1 if there is a memory allocation error
int readLineFromFile(FILE *file, int *totalLines, char ***lineContents) {
  *totalLines = 0;
  int currentLine = 0;
  char buffer[MAXLINELEN];

  // Calculate the total number of lines in the file
  while((fgets(buffer, sizeof(buffer), file) != NULL) && (strlen(buffer) < MAXLINELEN)) {
    (*totalLines)++;

    if(feof(file)) { // Check if the file pointer is at the end of the file
      break;
    }
  }

  // Rewind the file pointer to the beginning
  rewind(file);
  // Allocate memory for the line contents array
  *lineContents = (char **)malloc((size_t)(*totalLines) * sizeof(char *));

  if(*lineContents == NULL) {
    return -1; // Memory allocation error
  }

  // Read the file line by line and store the contents in the line contents array
  while(fgets(buffer, sizeof(buffer), file) != NULL) {
    if(lineContents == NULL) {
      return -1;
    }

    (*lineContents)[currentLine] = strndup(buffer, MAXLINELEN);
    currentLine++;
  }

  return 0;
}

void copyStringWithoutPrefix(const char *input, char *output, const char *prefix) {
  // Check if the input starts with the specified prefix
  if(strncmp(input, prefix, strlen(prefix)) == 0) {
    // Skip the prefix by moving the input pointer forward
    input += strlen(prefix);
  }

  // Copy the remaining part of the input to the output string
  strncpy(output, input, strlen(input));
}

char *expand_tilde(const char *path) {
  char *val2ret = NULL;

  if(path[0] == '~') {
    const char *homeDir = getenv("HOME");

    if(homeDir) {
      size_t pathLen = strlen(path);
      size_t homeDirLen = strlen(homeDir);
      char *expandedPath = malloc(homeDirLen + pathLen);

      if(expandedPath) {
        strncpy(expandedPath, homeDir, homeDirLen);
        strncat(expandedPath, path + 1, pathLen + (homeDirLen + 1));
        return expandedPath;
      }

      val2ret = strndup(path, pathLen);
    }
  }

  return val2ret;
}

// Uses: const char *command3 = "yes | sudo apt install gufw"; executeCommand(command3);
int executeCommand(const char *command) {
  pid_t pid = fork();

  if(pid == 0) {
    // This is the child process
    execl("/bin/sh", "sh", "-c", command, NULL);
    perror("execl failed");
    return 1;
  }

  if(pid > 0) {
    // This is the parent process
    int status;
    waitpid(pid, &status, 0);
    printf("Child process exited with status %d\n", WEXITSTATUS(status));
    // Open the file for appending
    const char *filePath = "~//scriptrunner.log";
    char *expandedPath = expand_tilde(filePath);
    /*printf("expandedPath: %s\n", expandedPath);*/
    FILE *logfile = fopen(expandedPath, "a");
    /*FILE *logfile = fopen("../scriptrunner.log", "a");*/

    if(logfile != NULL) {
      // Get current date and time
      time_t now = time(NULL);
      struct tm *tm_info = localtime(&now);
      char timestamp[20];
      (void)strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
      // Append the date-time stamp to the file
      (void)fprintf(logfile, "[%s] Command: %s, Exit Status: %d\n", timestamp, command, WEXITSTATUS(status));
      // Close the file
      (void)fclose(logfile);
      free(expandedPath);
    }

    else {
      printf("Failed to open the log file\n");
      free(expandedPath);
      return 1; // Error handling
    }

    return WEXITSTATUS(status);
  }

  // Otherwise, fork failed
  perror("fork failed");
  return 0;
}

void package_manager(char *package_manager_name) { // apt, yum, dnf, apx etc.
  int totalLines = 0;
  char **lineContents = NULL;
  FILE *fp = NULL;      /* input-file pointer */
  FILE *fp2 = NULL;     /* input-file pointer */
  char *fp_package_manager = "../.config/scriptrunner/package_manager.txt";      /* input-file name */
  const char *fp_package_manager_in_home_config = "~/.config/scriptrunner/package_manager.txt"; /* input-file name */
  char *expandedPath = expand_tilde(fp_package_manager_in_home_config);
  /*printf("expandedPath: %s\n", expandedPath);*/
  // try in the root folder first
  fp  = fopen(fp_package_manager, "r");

  /*if(fp != NULL) {*/
  /*(void)fprintf(stderr, "\nfn package_manager: fp. opened the file '%s'\n", fp_package_manager);*/
  /*}*/

  if(fp == NULL) { // try finding the file in the program's root directory (.config/scriptrunner)
    /*(void)fprintf(stderr, "\ncouldn't open file '%s'; %s\n", fp_package_manager,  strerror(errno));*/
    // Check if the file is in the home (~/.config/scriptrunner) directory
    fp2 = fopen(expandedPath, "r");

    if(fp2 == NULL) { // if not, exit permanently
      (void)fprintf(stderr, "\ncouldn't open file '%s'; %s\n", expandedPath,  strerror(errno));
      free(expandedPath);
      (void)fprintf(stderr, "\ncouldn't open file '%s', either; %s\n", fp_package_manager,  strerror(errno));
      exit(EXIT_FAILURE);
    }

    else { // means, the file is found in the home (~/.config/scriptrunner) directory, since (fp2 == NULL)
      /*(void)printf("File opened: %s. HOME dir flag set to ON.\n", expandedPath);*/
      home_config = 1; // from now on, consider that the file is in the home (~/.config/scriptrunner) directory // set the global flag on
    }
  }

  // Call the readLineFromFile function to read the contents of the file
  if(home_config == 0) {
    int result = readLineFromFile(fp, &totalLines, &lineContents);

    if(result != 0) {
      (void)fprintf(stderr, "\nError reading file. '%s'; %s\n", fp_package_manager,  strerror(errno));
      (void)fclose(fp);
    }

    /* copy the contents of the line no. 0 to the variable package_manager_name
      and pass it to package_manager_name */
    if(lineContents[0] != NULL) {
      strncpy(package_manager_name, *(lineContents + 0), MAXLINELEN);
    }
  }

  else if(home_config == 1) {
    int result = readLineFromFile(fp2, &totalLines, &lineContents);

    if(result != 0) {
      (void)fprintf(stderr, "\nError reading file. '%s'; %s\n", expandedPath,  strerror(errno));
      (void)fclose(fp);
    }

    /* copy the contents of the line no. 0 to the variable package_manager_name
      and pass it to package_manager_name */
    if(lineContents[0] != NULL) {
      strncpy(package_manager_name, *(lineContents + 0), MAXLINELEN);
    }
  }

  // Free the allocated memory for lineContents
  for(int i = 0; i < totalLines; i++) {
    free(lineContents[i]);
  }

  free(lineContents);
  lineContents = NULL;

  if(home_config == 0) {
    (void)fclose(fp); // Close the file
  }

  else if((home_config == 1) && (fp2 != NULL)) {
    (void)fclose(fp2); // Close the file
    free(expandedPath);
  }

  /*(void)printf("package_manager ran successfully!\n");*/
}

void install_command(char *command_2_install_apps) { // install, -S etc.
  int totalLines = 0;
  char **lineContents = NULL;
  FILE *file = NULL;      /* input-file pointer */
  FILE *file02 = NULL;      /* input-file pointer */
  char *file_install_command = "../.config/scriptrunner/installcommand.txt";      /* input-file name */
  const char *file_install_command_in_home_config = "~/.config/scriptrunner/installcommand.txt"; /* input-file name */
  char *expandedPath = expand_tilde(file_install_command_in_home_config);

  //
  if(home_config == 0) {
    file = fopen(file_install_command, "r"); /* input-file pointer */

    if(file == NULL) {
      (void)fprintf(stderr, "\ncouldn't open file '%s'; %s\n", file_install_command,  strerror(errno));
    }
  }

  else if(home_config == 1) {
    file02  = fopen(expandedPath, "r");

    if(file02 == NULL) {
      (void)fprintf(stderr, "\ncouldn't open file '%s'; %s\n", expandedPath,  strerror(errno));
      free(expandedPath);
      exit(EXIT_FAILURE);
    }
  }

  // Call the readLineFromFile function to read the contents of the file
  int result = '\0';

  if(home_config == 0) {
    result = readLineFromFile(file, &totalLines, &lineContents);
  }

  else if(home_config == 1) {
    result = readLineFromFile(file02, &totalLines, &lineContents);
  }

  if(result != 0) {
    (void)fprintf(stderr, "\nError reading file. '%s'; %s\n", file_install_command,  strerror(errno));
    (void)fclose(file);
  }

  /* copy the contents of the line no. 0 to the variable command_2_install_apps
    and pass it to command_2_install_apps */
  if(lineContents[0] != NULL) {
    strncpy(command_2_install_apps, *(lineContents + 0), MAXLINELEN);
  }

  // Free the allocated memory for lineContents
  for(int i = 0; i < totalLines; i++) {
    free(lineContents[i]);
  }

  free(lineContents);
  lineContents = NULL;

  if(home_config == 0) {
    (void)fclose(file); // Close the file
  }

  else if((home_config == 1) && (file02 != NULL)) {
    (void)fclose(file02); // Close the file
    free(expandedPath);
  }

  /*(void)printf("install_command ran successfully!\n");*/
}

int renewsys(void) {
  int totalLines = 0;
  FILE *file = NULL;
  FILE *file02 = NULL;      /* input-file pointer */
  char **lineContentsOfRenew = NULL;
  const char *renew_system_in_home_config = "~/.config/scriptrunner/renew_system.txt"; /* input-file name */
  char *expandedPath = expand_tilde(renew_system_in_home_config);

  if(home_config == 0) { // found in the root dir of the program
    file = fopen("../.config/scriptrunner/renew_system.txt", "r");

    if(file == NULL) {
      (void)printf("Failed to open the file.\n");
      return 1;
    }
  }

  else if(home_config == 1) {
    file02 = fopen(expandedPath, "r");

    if(file02 == NULL) {
      (void)printf("Failed to open the file.\n");
      free(expandedPath);
      return 1;
    }
  }

  // Call the readLineFromFile function to read the contents of the file
  int result = '\0';

  if(home_config == 0) {
    result = readLineFromFile(file, &totalLines, &lineContentsOfRenew);
  }

  else if(home_config == 1) {
    result = readLineFromFile(file02, &totalLines, &lineContentsOfRenew);
  }

  if(result != 0) {
    printf("Error reading file.\n");
    (void)fclose(file);
    return 1;
  }

  // Print the contents of each line
  for(int lineNumber = 1; lineNumber <= totalLines && lineContentsOfRenew[lineNumber - 1] != NULL; lineNumber++) {
    // if the first char of the line is '#', ignore the line alltogether
    if(lineContentsOfRenew[lineNumber - 1][0] == '#') {
      continue;
    }

    // if the first char of the line is NULL or '\n', i.e., the line is empty, ignore the line alltogether
    if(lineContentsOfRenew[lineNumber - 1][0] == '\0' || lineContentsOfRenew[lineNumber - 1][0] == '\n' || lineContentsOfRenew[lineNumber - 1][0] == '\t') {
      continue;
    }

    // if the first string in the line is "special: ", remove the string "special: " in memory, and print the remaing contents of the line
    if(strstr(lineContentsOfRenew[lineNumber - 1], "special: ") != NULL) {
      /*(void)printf("Line: %d, Line contents: %s, Found special.\n", lineNumber, lineContentsOfRenew[lineNumber - 1]);*/
      char inputLine[MAX_STRING_LENGTH_4_SPECIAL] = "";
      char lineContentsreduced[MAX_STRING_LENGTH_4_SPECIAL] = "";
      sf_strncpy(inputLine, lineContentsOfRenew[lineNumber - 1], MAX_STRING_LENGTH_4_SPECIAL);
      /*(void)printf("input line is: %s\n", inputLine);*/
      copyStringWithoutPrefix(inputLine, lineContentsreduced, "special: ");
      /*(void)printf("input after removing the prefix: %s\n", lineContentsreduced);*/
      (void)printf("Line %d: %s", lineNumber, lineContentsreduced);
      continue;
    }

    (void)printf("Command to pass from the line %d: %s", lineNumber, lineContentsOfRenew[lineNumber - 1]);
    executeCommand(lineContentsOfRenew[lineNumber - 1]);
  }

  // Free the allocated memory for lineContents
  for(int i = 0; i < totalLines; i++) {
    free(lineContentsOfRenew[i]);
    lineContentsOfRenew[i] = NULL;
  }

  free(lineContentsOfRenew);
  lineContentsOfRenew = NULL;

  // Free the allocated memory for lineContents
  /*(void)fclose(file); // Close the file*/
  if(home_config == 0) {
    (void)fclose(file); // Close the file
  }

  else if((home_config == 1) && (file02 != NULL)) {
    (void)fclose(file02); // Close the file
    free(expandedPath);
  }

  /*(void)printf("renewsys ran successfully!\n");*/
  return 0;
}

int package_installer(void) { // app installer
  char package_manager_name[MAXLINELEN] = "";
  package_manager(package_manager_name);
  /*(void)printf("manager: %s\n", package_manager_name);*/
  FILE *file = NULL;
  FILE *file02 = NULL;      /* input-file pointer */
  const char *package_installer_in_home_config = "~/.config/scriptrunner/apps.txt"; /* input-file name */
  char *expandedPath = expand_tilde(package_installer_in_home_config);

  if(home_config == 0) {
    file  = fopen("../.config/scriptrunner/apps.txt", "r");

    if(file == NULL) {
      (void)printf("Failed to open the file.\n");
      return 1;
    }
  }

  else if(home_config == 1) {
    file02  = fopen(expandedPath, "r");

    if(file02 == NULL) {
      (void)printf("Failed to open the file.\n");
      free(expandedPath);
      return 1;
    }
  }

  int totalLines = 0;
  char **lineContents = NULL;
  // Call the readLineFromFile function to read the contents of the file
  int result = '\0';

  if(home_config == 0) {
    result = readLineFromFile(file, &totalLines, &lineContents);
  }

  else if(home_config == 1) {
    result = readLineFromFile(file02, &totalLines, &lineContents);
  }

  if(result != 0) {
    printf("Error reading file.\n");
    (void)fclose(file);
    return 1;
  }

  // Print the contents of each line
  for(int lineNumber = 1; lineNumber <= totalLines && lineContents[lineNumber - 1] != NULL; lineNumber++) {
    // if the first char of the line is '#', ignore the line alltogether
    if(lineContents[lineNumber - 1][0] == '#') {
      continue;
    }

    // if the first char of the line is NULL or '\n', i.e., the line is empty, ignore the line alltogether
    if(lineContents[lineNumber - 1][0] == '\0' || lineContents[lineNumber - 1][0] == '\n' || lineContents[lineNumber - 1][0] == '\t') {
      continue;
    }

    // if the first string in the line is "special: ", remove the string "special: " in memory, and print the remaing contents of the line
    if(strstr(lineContents[lineNumber - 1], "special: ") != NULL) {
      /*(void)printf("Line: %d, Line contents: %s, Found special.\n", lineNumber, lineContents[lineNumber - 1]);*/
      char inputLine[MAX_STRING_LENGTH_4_SPECIAL] = "";
      char lineContentsreduced[MAX_STRING_LENGTH_4_SPECIAL] = "";
      sf_strncpy(inputLine, lineContents[lineNumber - 1], MAX_STRING_LENGTH_4_SPECIAL);
      /*(void)printf("input line is: %s\n", inputLine);*/
      copyStringWithoutPrefix(inputLine, lineContentsreduced, "special: ");
      /*(void)printf("input after removing the prefix: %s\n", lineContentsreduced);*/
      (void)printf("Command to pass from the line %d: %s", lineNumber, lineContentsreduced);
      executeCommand(lineContentsreduced);
      continue;
    }

    {
      char tmpstr2[MAX_STRING_LENGTH_4_SPECIAL] = "";
      char tmpstr3[MAX_STRING_LENGTH_4_SPECIAL] = "";
      char *the_package_manager = tmpstr2; // apt, yum etc.
      char *the_command_2_install_packages = tmpstr3; // install, -S etc.
      char totalcommandtopass[MAXLINELEN] = "";
      package_manager(the_package_manager);
      install_command(the_command_2_install_packages);
      /*(void)printf("The package manager found in the fn package_manager: %s\n", the_package_manager);*/
      /*(void)printf("The install command found in the fn install_command: %s\n", the_command_2_install_packages);*/
      /* concatenate SUDOCOMMAND, the_package_manager, INSTALLCOMMAND, and the contents of the line */
      sf_strncat(totalcommandtopass, PIPE_YES, MAXLINELEN); // 'yes |'
      sf_strncat(totalcommandtopass, " ", MAXLINELEN); // ' '
      sf_strncat(totalcommandtopass, SUDOCOMMAND, MAXLINELEN); // 'sudo'
      sf_strncat(totalcommandtopass, " ", MAXLINELEN); // ' '
      sf_strncat(totalcommandtopass, the_package_manager, MAXLINELEN);
      sf_strncat(totalcommandtopass, " ", MAXLINELEN);
      sf_strncat(totalcommandtopass, the_command_2_install_packages, MAXLINELEN);
      sf_strncat(totalcommandtopass, " ", MAXLINELEN);
      sf_strncat(totalcommandtopass, lineContents[lineNumber - 1], MAXLINELEN);
      (void)printf("Command to pass from the line %d: %s", lineNumber, totalcommandtopass);
      executeCommand(totalcommandtopass);
    }
  }

  // Free the allocated memory for lineContents
  for(int i = 0; i < totalLines; i++) {
    free(lineContents[i]);
    lineContents[i] = NULL;
  }

  free(lineContents);
  lineContents = NULL;

  // Free the allocated memory for lineContents
  if(home_config == 0) {
    (void)fclose(file); // Close the file
  }

  else if((home_config == 1) && (file02 != NULL)) {
    (void)fclose(file02); // Close the file
    free(expandedPath);
  }

  /*(void)printf("package_installer ran successfully!\n");*/
  return 0;
}

int main(int argc, char *argv[]) { /* The Main function. argc means the number of arguments. argv[0] is the program name. argv[1] is the first argument. argv[2] is the second argument and so on. */
  printf("Hey! \'%s\' here!\n", argv[0]); /* Displays the program's name */

  if(argc != NO_OF_ARGS) {  /* Checks if the program was called with the exact number of arguments. If it wasn't, it prints out an error message and returns 1. */
    printf("Please provide %d arguments\n", (NO_OF_ARGS - 1));
    return 1;
  }

  if(argc == 2 && strcmp(argv[1], "--version") == 0) { /* checks if the program was called with the argument "--version". If it was, it prints out the value of the "VERSION" constant and returns 0. Otherwise, it slides down to the next `if()` block. */
    printf("%s\n", VERSION);
    return 0;
  }

  if(argc == 2 && strcmp(argv[1], "-r") == 0) { /* checks if the program was called with only ONE argument and the argument was "-r" (run). In that case, the program executes. */
    // the 2nd part
    char package_manager_name[MAXLINELEN] = "";
    package_manager(package_manager_name);
    printf("package manager: %s\n", package_manager_name);
    char installcommandname[MAXLINELEN] = "";
    install_command(installcommandname);
    printf("install command: %s\n", installcommandname);
    // ask the user to choose an option 1. update the system, 2. install the packages, 3. quit
    int option = 0;
    (void)printf("Choose an option:\n1. update the system\n2. install the packages\n3. update the system & install the packages\n4. quit\n");
    sf_scanf("%d", &option, MAX_INPUT);

    switch(option) {
      case 1:
        (void)renewsys();
        break;

      case 2:
        (void)package_installer();
        break;

      case 3:
        (void)renewsys();
        (void)package_installer();
        break;

      case 4:
        return(0);
        break;

      default:
        (void)printf("Invalid option.\n");
        break;
    }
  }

  if((argc == 2 && strcmp(argv[1], "--version") != 0) && (argc == 2 && strcmp(argv[1], "-r") != 0)) {
    printf("Please provide a valid argument\n");
  }

  printf("Supplied argument: %s\n", argv[1]); /* prints out the first argument passed to the program */
  return 0;
}
