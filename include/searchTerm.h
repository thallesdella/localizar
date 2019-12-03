//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_SEARCHTERM_H
#define LOCALIZA_SEARCHTERM_H

#include "structs.h"
#include "dstring.h"

void initSearchTerm(SearchTerm *searchTerm);

void addSearchTerm(SearchTerm *searchTerm, dString term);

void removeSearchTermFromLine(dString line, SearchTerm term);

#endif //LOCALIZA_SEARCHTERM_H
