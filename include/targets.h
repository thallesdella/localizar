//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_TARGETS_H
#define LOCALIZA_TARGETS_H

#include "structs.h"
#include "dstring.h"

int searchInTarget(SearchTerm needle, dString targetPath, Flags flags);

void scanDir(Targets *target, dString path);

void initTargets(Targets *target);

void addTarget(Targets *target, dString targetPath);

dString getTargetPath(Targets target, unsigned int id);

int verifySearchTermPresence(SearchTerm needle, dString haystack, Flags flags);

#endif //LOCALIZA_TARGETS_H
