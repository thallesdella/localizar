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

int newLinePosition(FILE *stream, long int start) {
  int c = 0, i = 0;
  while (c != '\n' && !feof(stream)) {
    i = ftell(stream);
    c = fgetc(stream);
  }
  fseek(stream, start, SEEK_SET);
  return i;
}

int fileExists(dString path) {
  Stat statBuf;
  if (stat(path, &statBuf) == 0) {
    return 1;
  }
  return 0;
}

int isFile(dString path) {
  Stat statBuf;
  stat(path, &statBuf);

  if (stat(path, &statBuf) == 0) {
    return S_ISREG(statBuf.st_mode);
  }
  return 0;
}

int isDir(dString path) {
  Stat statBuf;

  if (stat(path, &statBuf) == 0) {
    return S_ISDIR(statBuf.st_mode);
  }
  return 0;
}

int randInt() {
  srand(time(0));
  return rand();
}

void printDebugMsg(dString msg) {
  if (superGlobal.isDebug == 1) {
    printf("%s\n", msg);
  }
}