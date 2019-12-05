//
// Created by THALLES on 19/11/2019.
//

#include "helpers.h"
#include "dstring.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

/**
 * Function: newLinePosition
 * ----------------------------
 *   @brief find the next end of the line.
 *
 *   @param stream file stream.
 *   @param start position of file's start.
 *
 *   @return new line char position.
 */
int newLinePosition(FILE *stream, long int start) {
  int c = 0, i = 0;
  while (c != '\n' && !feof(stream)) {
    i = ftell(stream);
    c = fgetc(stream);
  }
  fseek(stream, start, SEEK_SET);
  return i;
}

/**
 * Function: fileExists
 * ----------------------------
 *   @brief Verify if file exists.
 *
 *   @param path path to file.
 *
 *   @return 1 for true and 0 for false.
 */
int fileExists(dString path) {
  Stat statBuf;
  if (stat(path, &statBuf) == 0) {
    return 1;
  }
  return 0;
}

/**
 * Function: isFile
 * ----------------------------
 *   @brief verify if is file.
 *
 *   @param path path to file.
 *
 *   @return 1 for true and 0 for false.
 */
int isFile(dString path) {
  Stat statBuf;
  stat(path, &statBuf);

  if (stat(path, &statBuf) == 0) {
    return S_ISREG(statBuf.st_mode);
  }
  return 0;
}

/**
 * Function: isDir
 * ----------------------------
 *   @brief verify if is directory.
 *
 *   @param path path to file.
 *
 *   @return 1 for true and 0 for false.
 */
int isDir(dString path) {
  Stat statBuf;

  if (stat(path, &statBuf) == 0) {
    return S_ISDIR(statBuf.st_mode);
  }
  return 0;
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