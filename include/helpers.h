//
// Created by THALLES on 19/11/2019.
//

#ifndef LOCALIZA_HELPERS_H
#define LOCALIZA_HELPERS_H

#include "dstring.h"
#include "structs.h"

int newLinePosition(void *stream, long int start);

int randInt();

void printDebugMsg(dString msg);

dString generateName(dString baseName);

#endif // LOCALIZA_HELPERS_H
