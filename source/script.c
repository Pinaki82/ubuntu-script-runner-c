// Last Change: 2023-06-09  Friday: 11:41:35 PM
// #!/usr/bin/c -Wall -Wextra -pedantic --std=c99
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "sf_c.h"

#define MAXLINELEN 2048
#define MAX_STRING_LENGTH_4_SPECIAL 100
#define PIPE_YES  "yes |"
#define SUDOCOMMAND  "sudo"
#define strndup  sf_strndup

int readLineFromFile(FILE *file, int *totalLines, char ***lineContents);
void copyStringWithoutPrefix(const char *input, char *output, const char *prefix);
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

void package_manager(char *package_manager_name) { // apt, yum, dnf, apx etc.
  int totalLines = 0;
  char **lineContents = NULL;
  FILE  *fp;      /* input-file pointer */
  char  *fp_package_manager = "../.config/scriptrunner/package_manager.txt";      /* input-file name */ /* use extension within double quotes */
  fp  = fopen(fp_package_manager, "r");

  if(fp == NULL) {
    (void)fprintf(stderr, "\ncouldn't open file '%s'; %s\n", fp_package_manager,  strerror(errno));
    exit(EXIT_FAILURE);
  }

  // Call the readLineFromFile function to read the contents of the file
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

  // Free the allocated memory for lineContents
  for(int i = 0; i < totalLines; i++) {
    free(lineContents[i]);
  }

  free(lineContents);
  lineContents = NULL;
  (void)fclose(fp); // Close the file
}

void install_command(char *command_2_install_apps) { // install, -S etc.
  int totalLines = 0;
  char **lineContents = NULL;
  FILE  *file;      /* input-file pointer */
  char  *file_install_command = "../.config/scriptrunner/installcommand.txt";      /* input-file name */ /* use extension within double quotes */
  file  = fopen(file_install_command, "r");

  if(file == NULL) {
    (void)fprintf(stderr, "\ncouldn't open file '%s'; %s\n", file_install_command,  strerror(errno));
    exit(EXIT_FAILURE);
  }

  // Call the readLineFromFile function to read the contents of the file
  int result = readLineFromFile(file, &totalLines, &lineContents);

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
  (void)fclose(file); // Close the file
}

int renewsys(void) {
  /* part 3 */
  FILE *file02 = fopen("../.config/scriptrunner/renew_system.txt", "r");

  if(file02 == NULL) {
    (void)printf("Failed to open the file.\n");
    return 1;
  }

  int totalLines2 = 0;
  char *tmpstr = "";
  char **lineContentsOfRenew = &tmpstr;
  // Call the readLineFromFile function to read the contents of the file
  int result = readLineFromFile(file02, &totalLines2, &lineContentsOfRenew);

  if(result != 0) {
    printf("Error reading file.\n");
    (void)fclose(file02);
    return 1;
  }

  // Print the contents of each line
  for(int lineNumber = 1; lineNumber <= totalLines2 && lineContentsOfRenew[lineNumber - 1] != NULL; lineNumber++) {
    (void)printf("Line %d: %s", lineNumber, lineContentsOfRenew[lineNumber - 1]);
  }

  // Free the allocated memory for lineContents
  for(int i = 0; i < totalLines2; i++) {
    free(lineContentsOfRenew[i]);
    lineContentsOfRenew[i] = NULL;
  }

  free(lineContentsOfRenew);
  lineContentsOfRenew = NULL;
  // Free the allocated memory for lineContents
  (void)fclose(file02); // Close the file
  return 0;
}

int package_installer(void) { // app installer
  char package_manager_name[MAXLINELEN] = "";
  package_manager(package_manager_name);
  /*(void)printf("manager: %s\n", package_manager_name);*/
  FILE *file = fopen("../.config/scriptrunner/apps.txt", "r");

  if(file == NULL) {
    (void)printf("Failed to open the file.\n");
    return 1;
  }

  int totalLines = 0;
  char *tmpstr = "";
  char **lineContents = &tmpstr;
  // Call the readLineFromFile function to read the contents of the file
  int result = readLineFromFile(file, &totalLines, &lineContents);

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
      sf_strncat(totalcommandtopass, PIPE_YES, MAXLINELEN);
      sf_strncat(totalcommandtopass, " ", MAXLINELEN);
      sf_strncat(totalcommandtopass, SUDOCOMMAND, MAXLINELEN);
      sf_strncat(totalcommandtopass, " ", MAXLINELEN);
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
  (void)fclose(file); // Close the file
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

