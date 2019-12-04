//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_STRUCTS_H
#define LOCALIZA_STRUCTS_H

#include "dstring.h"

typedef struct Option {
    int status;

    int (*verify)(dString str);
} Option;

typedef struct Flags {
    unsigned int count;
    unsigned int active;
    Option *flags;
} Flags;

typedef struct SearchTerm {
    unsigned int count;
    dStringVector terms;
} SearchTerm;

typedef struct Target {
    int isFile;
    int isDir;
    unsigned int hotLines;
    unsigned int occurrences;
    dString path;
} Target;

typedef struct Targets {
    unsigned int count;
    unsigned int totalHotLines;
    unsigned int totalOccurrences;
    Target *targets;
} Targets;

typedef struct SuperGlobal {
    int (*isDebug)(void);
} SuperGlobal;

SuperGlobal superGlobal;

#endif //LOCALIZA_STRUCTS_H
