//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_STRUCTS_H
#define LOCALIZA_STRUCTS_H

#include "dstring.h"

typedef struct Target {
    int isFile;
    int isDir;
    unsigned int occurrences;
    dString path;
} Target;

typedef struct Targets {
    unsigned int count;
    unsigned int pathMaxLength;
    unsigned int totalOccurrences;
    Target *targets;
} Targets;

typedef struct Option {
    int status;

    int (*verify)(dString str);
} Option;

typedef struct Flags {
    int count;
    int active;
    Option *flags;
} Flags;

#endif //LOCALIZA_STRUCTS_H
