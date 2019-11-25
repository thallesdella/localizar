//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_TARGETS_H
#define LOCALIZA_TARGETS_H

#include "helpers/structs.h"
#include "helpers/dstring.h"

int searchInTarget(Flags flags, SearchTerm searchTerm, dString targetPath);

void scanDir(Targets *target, dString path);

void initTargets(Targets *target);

void addTarget(Targets *target, dString targetPath);

dString getTargetPath(Targets target, unsigned int id);

#endif //LOCALIZA_TARGETS_H
