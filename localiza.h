//
// Created by THALLES on 18/11/2019.
//

#ifndef LOCALIZA_LOCALIZA_H
#define LOCALIZA_LOCALIZA_H

#include "dstring.h"

typedef struct Targets {
    int count;
    dStringVector targets;
} Targets;

Targets targets;

dString sSearchTerm;

void help(dString scriptname, int exitCode);

void getFlagsFromArg(int argc, dStringVector argv);

void getSearchTermFromArg(dStringVector argv);

void getTargetsFromArg(int argc, dStringVector argv);

void parseArguments(int argc, dStringVector argv);

void garbageCollector();

int newLinePosition(FILE *stream, long int start);

void grep(dString searchTerm);

int main(int argc, dStringVector argv);

#endif //LOCALIZA_LOCALIZA_H
