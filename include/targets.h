//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_TARGETS_H
#define LOCALIZA_TARGETS_H

#include "helpers.h"

void initTargets(Targets *target);

void addTarget(Targets *target, dString targetPath);

int *searchInTarget(SearchTerm needle, File target, Flags flags);

dString getTargetPath(Targets target, unsigned int id);

#endif // LOCALIZA_TARGETS_H
