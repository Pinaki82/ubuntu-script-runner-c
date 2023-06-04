// Last Change: 2023-06-03  Saturday: 01:44:24 PM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sf_c.h"

#define MAXLINELEN 2048

int readLineFromFile(FILE *file, int *totalLines, int lineNumber, char ***lineContents, int freeMemory);

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
  while(fgets(buffer, sizeof(buffer), file) != NULL) {
    (*totalLines)++;
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

int main() {
}

