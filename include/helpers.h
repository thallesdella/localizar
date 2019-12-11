//
// Created by THALLES on 19/11/2019.
//

#ifndef LOCALIZA_HELPERS_H
#define LOCALIZA_HELPERS_H

#include "structs.h"

int newLinePosition(void *stream, long int start);

unsigned int randInt(unsigned int max, unsigned int min);

void printDebugMsg(dString msg);

dString generateName(dString baseName, dString ext);

#endif // LOCALIZA_HELPERS_H
