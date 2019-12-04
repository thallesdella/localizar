//
// Created by Thalles on 21/11/2019.
//

#include <stdio.h>
#include "searchTerm.h"
#include "structs.h"
#include "dstring.h"

void initSearchTerm(SearchTerm *searchTerm) {
    searchTerm->count = 0;
    searchTerm->terms = initStringVector(searchTerm->count);
}

void addSearchTerm(SearchTerm *searchTerm, dString term) {
    searchTerm->count = countAppearances(term, "*") + 1;

    if (searchTerm->count > 1) {
        explode(term, "*", searchTerm->terms);
    } else {
        searchTerm->count = 1;
        searchTerm->terms[0] = initString(term);
    }

    if (superGlobal.isDebug == 1) {
        for (int i = 0; i < searchTerm->count; ++i) {
            printf("[ADD_SEARCH_TERM] %s\n", searchTerm->terms[i]);
        }
    }
}

void removeSearchTermFromLine(dString line, SearchTerm term) {
    for (int i = 0; i < term.count; ++i) {
        removeSubstr(line, term.terms[i]);
    }
}
