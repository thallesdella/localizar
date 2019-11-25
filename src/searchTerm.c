//
// Created by Thalles on 21/11/2019.
//

#include "searchTerm.h"
#include "helpers/structs.h"
#include "helpers/dstring.h"

void initSearchTerm(SearchTerm *searchTerm) {
    searchTerm->count = 0;
    searchTerm->terms = initStringVector(searchTerm->count);
}

void addSearchTerm(SearchTerm *searchTerm, dString term) {
    searchTerm->count = countAppearances(term, "*");

    if (searchTerm->count > 1) {
        explode(term, "*", searchTerm->terms);
    } else {
        searchTerm->count = 1;
        searchTerm->terms[0] = initString(term);
    }
}
