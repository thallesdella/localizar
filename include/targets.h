//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_TARGETS_H
#define LOCALIZA_TARGETS_H

#include "dstring.h"
#include "structs.h"
#include <stdio.h>

int *searchInTarget(SearchTerm needle, dString targetPath, Flags flags);

void scanDir(Targets *target, dString path);

void initTargets(Targets *target);

void addTarget(Targets *target, dString targetPath);

void generateOutputFile(dString name, dString content);

void generateName(dString baseName);

void printMsgForFile(Targets target, unsigned int id, dString message);

dString getTargetPath(Targets target, unsigned int id);

void readLine(FILE *file, dString line);

int countSearchTermOccurrence(SearchTerm needle, dString haystack, Flags flags);

int verifySearchTermPresence(SearchTerm needle, dString haystack, Flags flags);

#endif // LOCALIZA_TARGETS_H
