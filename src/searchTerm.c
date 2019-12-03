//
// Created by Thalles on 21/11/2019.
//

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
}

void removeSearchTermFromLine(dString line, SearchTerm term) {
    for (int i = 0; i < term.count; ++i) {
        removeSubstr(line, term.terms[i]);
    }
}
