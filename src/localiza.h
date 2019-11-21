//
// Created by THALLES on 18/11/2019.
//

#ifndef LOCALIZA_LOCALIZA_H
#define LOCALIZA_LOCALIZA_H

#include "helpers/structs.h"
#include "flags.h"
#include "targets.h"
#include "helpers/dstring.h"

#define FLAGS_COUNT 5

Option *options;
Flags flags;
dString sSearchTerm;
Targets targets;

void getFlagsFromArg(int argc, dStringVector argv);

void getSearchTermFromArg(dStringVector argv);

void getTargetsFromArg(int argc, dStringVector argv);

void parseArguments(int argc, dStringVector argv);

void grep(dString searchTerm);

void garbageCollector(void);

int main(int argc, dStringVector argv);

#endif //LOCALIZA_LOCALIZA_H
