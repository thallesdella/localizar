//
// Created by THALLES on 19/11/2019.
//

#include "helpers.h"
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
void generateName(dString baseName) {
  dString buf = initString(baseName);
  int count = countAppearances(buf, ".");

  dStringVector rand = initStringVector(2);
  intToStr(rand[0], randInt());
  intToStr(rand[1], randInt());

  if (count == 0) {
    baseName = concatStr(baseName, 3, "_", rand[0], rand[1]);
    return;
  }

  dStringVector bufVec = initStringVector(count);
  explode(buf, ".", bufVec);

  bufVec[count - 1] = concatStr(bufVec[count - 1], 3, "_", rand[0], rand[1]);

  implode(bufVec, count, ".", buf);
  alterString(baseName, buf);

  freeStringVector(bufVec, count);
  freeString(buf);
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