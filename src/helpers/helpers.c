//
// Created by THALLES on 19/11/2019.
//

#include "helpers.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Function: newLinePosition
 * ----------------------------
 *   @brief find the next end of the line.
 *
 *   @param stream pointer to a file stream.
 *   @param start position of file's start.
 *
 *   @return new line char position.
 */
int newLinePosition(void *stream, long int start) {
  FILE *file = (FILE *)stream;
  int c = 0, i = 0;
  while (c != '\n' && !feof(file)) {
    i = ftell(file);
    c = fgetc(file);
  }
  fseek(file, start, SEEK_SET);
  return i;
}

/**
 * Function: randInt
 * ----------------------------
 *   @brief generate a random int.
 *
 *   @return a random int.
 */
int randInt() {
  srand(time(0));
  return rand();
}

/**
 * Function: generateName
 * ----------------------------
 *   @brief Generate a new name adding random number to the end of the
 *      files's name.
 *
 *   @category Output File
 *
 *   @param baseName name to be altered.
 */
dString generateName(dString baseName) {
  dString extension = getFileExtension(baseName);
  printf("extension:%s\n", extension);
  return extension;
}

/**
 * Function: printDebugMsg
 * ----------------------------
 *   @brief print debug message
 *
 *   @param msg message to be displayed.
 */
void printDebugMsg(dString msg) {
  if (superGlobal.isDebug == 1) {
    printf("%s\n", msg);
  }
}