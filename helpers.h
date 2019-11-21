//
// Created by THALLES on 19/11/2019.
//

#ifndef LOCALIZA_HELPERS_H
#define LOCALIZA_HELPERS_H

#include <stdio.h>
#include "dstring.h"

typedef struct stat Stat;

int newLinePosition(FILE *stream, long int start);

int isFile(dString path);

int isDir(dString path);

#endif //LOCALIZA_HELPERS_H
