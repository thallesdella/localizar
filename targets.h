//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_TARGETS_H
#define LOCALIZA_TARGETS_H

#include "dstring.h"

typedef struct stat Stat;

typedef struct Target {
    int isFile;
    int isDir;
    unsigned int occurrences;
    dString path;
} Target;

typedef struct Targets {
    unsigned int count;
    unsigned int totalOccurrences;
    Target *targets;
} Targets;

Targets targets;

int isFile(dString path);

int isDir(dString path);

int searchInTarget(dString searchTerm, dString targetPath);

dString getTargetPath(int id);

#endif //LOCALIZA_TARGETS_H
