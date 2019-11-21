//
// Created by THALLES on 18/11/2019.
//

#ifndef LOCALIZA_LOCALIZA_H
#define LOCALIZA_LOCALIZA_H

#include "dstring.h"

typedef struct Target {
    int isFile;
    int isDir;
    unsigned int occurrences;
    dString path;
} Target;

typedef struct Targets {
    size_t count;
    unsigned int totalOccurrences;
    Target *targets;
} Targets;

Targets targets;
dString sSearchTerm;

void getFlagsFromArg(int argc, dStringVector argv);

void getSearchTermFromArg(dStringVector argv);

void getTargetsFromArg(int argc, dStringVector argv);

void parseArguments(int argc, dStringVector argv);

int newLinePosition(FILE *stream, long int start);

void grep(dString searchTerm);

void garbageCollector(void);

int main(int argc, dStringVector argv);

#endif //LOCALIZA_LOCALIZA_H
