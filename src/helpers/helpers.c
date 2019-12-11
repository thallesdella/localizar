//
// Created by THALLES on 19/11/2019.
//

#include "helpers.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
 *   @param max maximum that a generated number can reach.
 *   @param min minimum that a generated number can reach.
 *
 *   @return random int between max an min.
 */
unsigned int randInt(unsigned int max, unsigned int min) {
  max = (max <= 0 || max > RAND_MAX ? RAND_MAX : max);
  srand(time(NULL));
  return (rand() % (max - min + 1)) + min;
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
dString generateName(dString baseName, dString ext) {
  dString buf = malloc(sizeof(char) * (strlen(baseName) + strlen(ext) + 11));
  sprintf(buf, "%s_%d%d.%s", baseName, randInt(9999, 1000), randInt(9999, 1000),
          ext);
  return buf;
}