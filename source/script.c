// Last Change: 2023-06-06  Tuesday: 10:09:02 PM
// #!/usr/bin/c -Wall -Wextra -pedantic --std=c99
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include "sf_c.h"

#define MAXLINELEN 2048

int readLineFromFile(FILE *file, int *totalLines, int lineNumber, char ***lineContents, int freeMemory);
void package_manager(char *package_manager_name, int freememory);

// Function to read from a text file line by line
// Arguments:
//   file: The file pointer to read from
//   totalLines: A pointer to store the total number of lines in the file
//   lineNumber: The line number the user wants to read
//   lineContents: A pointer to store the contents of the requested line
//   freeMemory: A flag indicating whether to free the allocated memory (0 - don't free, 1 - free)
// Returns:
//   0 if the function executes successfully, -1 if there is a memory allocation error
int readLineFromFile(FILE *file, int *totalLines, int lineNumber, char ***lineContents, int freeMemory) {
  int currentLine = 0;
  char buffer[MAXLINELEN] = ""; // Use buffer size of 2048
  int temp01 = 0;
  *totalLines = temp01;

  // Calculate the total number of lines in the file
  while((fgets(buffer, sizeof(buffer), file) != NULL) && (strlen(buffer) < MAXLINELEN)) {
    (*totalLines)++;

    if(feof(file)) { // Check if the file pointer is at the end of the file
      break;
    }
  }

  // Rewind the file pointer to the beginning
  rewind(file);

  // If the user only wants to know the total number of lines, return here
  if(lineNumber == 0 && lineContents == NULL) {
    return 0;
  }

  // Allocate memory for the line contents array
  *lineContents = (char **)malloc((size_t)(*totalLines) * sizeof(char *));

  if(*lineContents == NULL) {
    return -1; // Memory allocation error
  }

  // Read the file line by line and store the contents in the line contents array
  while(fgets(buffer, sizeof(buffer), file) != NULL) {
    (*lineContents)[currentLine] = strdup(buffer);

    // If the line number matches the requested line, store the contents
    if(currentLine == lineNumber - 1 && lineContents != NULL) {
      *(*lineContents + currentLine) = strdup(buffer); // Update line storage
    }

    currentLine++;
  }

  // If the user only wants to know the contents of a specific line, return here
  if(lineNumber != 0 && lineContents != NULL) {
    return 0;
  }

  // If the user wants to free the allocated memory, do so
  if(freeMemory) {
    for(int i = 0; i < *totalLines; i++) {
      free((*lineContents)[i]);
    }

    free(*lineContents);
  }

  return 0;
}

void package_manager(char *package_manager_name, int freememory) {
  int totalLines = 0;
  int lineNumber = 0; // the first line, also initialise the variable
  char **lineContents = NULL;
  FILE  *fp;      /* input-file pointer */
  char  *fp_package_manager = "../.config/scriptrunner/package_manager.txt";      /* input-file name */ /* use extension within double quotes */
  fp  = fopen(fp_package_manager, "r");

  if(fp == NULL) {
    (void)fprintf(stderr, "\ncouldn't open file '%s'; %s\n", fp_package_manager,  strerror(errno));
    exit(EXIT_FAILURE);
  }

  else if(fp != NULL) {
    // Call the readLineFromFile function to read the contents of line number 2
    readLineFromFile(fp, &totalLines, lineNumber, &lineContents, 0);

    /* copy the contents of the line no. 0 to the variable package_manager_name
      and pass it to the function's argument variable pointer, package_manager_name */
    if(lineContents != NULL) {
      /*(void)printf("Line %d: %s\n", lineNumber, *lineContents);*/
      strncpy(package_manager_name, *lineContents, MAXLINELEN);
    }

    if((fclose(fp) == EOF) && (freememory == 0))  {    /* close input file */
      free(lineContents); // Free the allocated memory for lineContents
      (void)fprintf(stderr, "\ncouldn't close file '%s'; %s\n", fp_package_manager,  strerror(errno));
      exit(EXIT_FAILURE);
    }

    else if(freememory == 1) {
      free(lineContents); // Free the allocated memory for lineContents
    }

    else {
      free(lineContents); // Free the allocated memory for lineContents
    }
  }
}

int main() {
  FILE *file = fopen("../example.txt", "r");

  if(file == NULL) {
    (void)printf("Failed to open the file.\n");
    return 1;
  }

  int totalLines;
  int lineNumber = 2;
  char **lineContents = NULL;
  // Call the readLineFromFile function to read the contents of line number 2
  readLineFromFile(file, &totalLines, lineNumber, &lineContents, 0);

  // Print the contents of line number 2
  if(lineContents != NULL) {
    (void)printf("Line %d: %s\n", lineNumber, *lineContents);
    free(lineContents); // Free the allocated memory for lineContents
  }

  (void)fclose(file); // Close the file
  char package_manager_name[MAXLINELEN] = "";
  package_manager(package_manager_name, 1);
  printf("Your package manager is: %s\n", package_manager_name);
  return 0;
}

