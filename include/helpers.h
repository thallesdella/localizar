//
// Created by THALLES on 19/11/2019.
//

#ifndef LOCALIZA_HELPERS_H
#define LOCALIZA_HELPERS_H

#include "dstring.h"
#include "structs.h"

int newLinePosition(void *stream, long int start);

int isFile(dString path);

int isDir(dString path);

int randInt();

void generateName(dString baseName);

void printDebugMsg(dString msg);

#endif // LOCALIZA_HELPERS_H
