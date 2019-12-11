//
// Created by Thalles on 21/11/2019.
//

#ifndef LOCALIZA_SEARCHTERM_H
#define LOCALIZA_SEARCHTERM_H

#include "helpers.h"

void initSearchTerm(SearchTerm *searchTerm);

void addSearchTerm(SearchTerm *searchTerm, dString term);

void removeSearchTermFromString(dString string, SearchTerm searchTerm);

int countSearchTermOccurrence(SearchTerm needle, dString haystack, Flags flags);

int verifySearchTermPresence(SearchTerm needle, dString haystack, Flags flags);

#endif // LOCALIZA_SEARCHTERM_H
