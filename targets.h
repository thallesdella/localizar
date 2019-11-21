//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_TARGETS_H
#define LOCALIZA_TARGETS_H

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

Targets targets;

int searchInTarget(dString searchTerm, dString targetPath);

void scanDir(dString path);

void initTargets(Targets *initTarget);

void addTarget(dString targetPath, unsigned int targetPathLen);

dString getTargetPath(unsigned int id);

#endif //LOCALIZA_TARGETS_H
