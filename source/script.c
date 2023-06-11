// Last Change: 2023-06-10  Saturday: 09:28:46 PM
// #!/usr/bin/c -Wall -Wextra -pedantic --std=c99
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "sf_c.h"

#define MAXLINELEN 2048
#define MAX_STRING_LENGTH_4_SPECIAL 100
#define PIPE_YES  "yes |"
#define SUDOCOMMAND  "sudo"
#define strndup  sf_strndup

int home_config = 0; // global flag to check if the file is in the home (~/.config/scriptrunner) directory. 0 means the file is in the root of the program's folder

int readLineFromFile(FILE *file, int *totalLines, char ***lineContents);
void copyStringWithoutPrefix(const char *input, char *output, const char *prefix);
char *expand_tilde(const char *path);
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
  strcpy(output, input);
}

char *expand_tilde(const char *path) {
  if(path[0] == '~') {
    const char *homeDir = getenv("HOME");

    if(homeDir) {
      size_t pathLen = strlen(path);
      size_t homeDirLen = strlen(homeDir);
      char *expandedPath = malloc(homeDirLen + pathLen);

      if(expandedPath) {
        strcpy(expandedPath, homeDir);
        strcat(expandedPath, path + 1);
        return expandedPath;
      }
    }
  }

  return strdup(path);
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
  char *tmpstr = "";
  char **lineContentsOfRenew = &tmpstr;
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

    // else if the first char of the line is NULL or '\n', i.e., the line is empty, ignore the line alltogether
    else if(lineContentsOfRenew[lineNumber - 1][0] == '\0' || lineContentsOfRenew[lineNumber - 1][0] == '\n' || lineContentsOfRenew[lineNumber - 1][0] == '\t') {
      continue;
    }

    // else if the the first string in the line is "special: ", remove the string "special: " in memory, and print the remaing contents of the line
    else if(strstr(lineContentsOfRenew[lineNumber - 1], "special: ") != NULL) {
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

    else {
      (void)printf("Line %d: %s", lineNumber, lineContentsOfRenew[lineNumber - 1]);
    }
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
  char *tmpstr = "";
  char **lineContents = &tmpstr;
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

    // else if the first char of the line is NULL or '\n', i.e., the line is empty, ignore the line alltogether
    else if(lineContents[lineNumber - 1][0] == '\0' || lineContents[lineNumber - 1][0] == '\n' || lineContents[lineNumber - 1][0] == '\t') {
      continue;
    }

    // else if the the first string in the line is "special: ", remove the string "special: " in memory, and print the remaing contents of the line
    else if(strstr(lineContents[lineNumber - 1], "special: ") != NULL) {
      /*(void)printf("Line: %d, Line contents: %s, Found special.\n", lineNumber, lineContents[lineNumber - 1]);*/
      char inputLine[MAX_STRING_LENGTH_4_SPECIAL] = "";
      char lineContentsreduced[MAX_STRING_LENGTH_4_SPECIAL] = "";
      sf_strncpy(inputLine, lineContents[lineNumber - 1], MAX_STRING_LENGTH_4_SPECIAL);
      /*(void)printf("input line is: %s\n", inputLine);*/
      copyStringWithoutPrefix(inputLine, lineContentsreduced, "special: ");
      /*(void)printf("input after removing the prefix: %s\n", lineContentsreduced);*/
      (void)printf("Line %d: %s", lineNumber, lineContentsreduced);
      continue;
    }

    else {
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
      (void)printf("Line %d: %s", lineNumber, totalcommandtopass);
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
int main() {
  // the 2nd part
  char package_manager_name[MAXLINELEN] = "";
  package_manager(package_manager_name);
  printf("package manager: %s\n", package_manager_name);
  char installcommandname[MAXLINELEN] = "";
  install_command(installcommandname);
  printf("install command: %s\n", installcommandname);
  (void)renewsys();
  (void)package_installer();
  return 0;
}
