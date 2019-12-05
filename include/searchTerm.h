//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_SEARCHTERM_H
#define LOCALIZA_SEARCHTERM_H

#include "dstring.h"
#include "structs.h"

void initSearchTerm(SearchTerm *searchTerm);

void addSearchTerm(SearchTerm *searchTerm, dString term);

void removeSearchTermFromString(dString string, SearchTerm searchTerm);

#endif // LOCALIZA_SEARCHTERM_H
