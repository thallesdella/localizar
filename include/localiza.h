//
// Created by THALLES on 18/11/2019.
//

#ifndef LOCALIZA_LOCALIZA_H
#define LOCALIZA_LOCALIZA_H

#include "structs.h"
#include "flags.h"
#include "targets.h"
#include "dstring.h"

#define FLAGS_COUNT 6

Option *options;
Flags flags;
SearchTerm searchTerm;
Targets targets;

int isDebug(void);

void getFlagsFromArg(int argc, dStringVector argv);

void getSearchTermFromArg(dStringVector argv);

void getTargetsFromArg(int argc, dStringVector argv);

void parseArguments(int argc, dStringVector argv);

void grep(void);

void garbageCollector(void);

int main(int argc, dStringVector argv);

#endif //LOCALIZA_LOCALIZA_H
