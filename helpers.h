//
// Created by THALLES on 19/11/2019.
//

#ifndef LOCALIZA_HELPERS_H
#define LOCALIZA_HELPERS_H

#include "dstring.h"

typedef struct stat Stat;

unsigned int maxLength(unsigned int size, dStringVector matrix);

unsigned int maxLengthTargetPath(dString newPath);

int newLinePosition(FILE *stream, long int start);

dString strToLower(dString string);

dString strToUpper(dString string);

int isFile(dString path);

int isDir(dString path);

#endif //LOCALIZA_HELPERS_H
