//
// Created by Thalles on 21/11/2019.
//

#include <stdlib.h>
#include <string.h>
#include "searchTerm.h"
#include "helpers/structs.h"
#include "helpers/dstring.h"

void initSearchTerm(SearchTerm *searchTerm) {
    searchTerm->count = 0;
    searchTerm->terms = malloc(sizeof(dString));
}

void addSearchTerm(SearchTerm *searchTerm, dString term) {
    searchTerm->count = countAppearances(term, "*");

    if (searchTerm->count > 1) {
        explode(term, "*", searchTerm->terms);
    } else {
        searchTerm->count = 1;
        searchTerm->terms[0] = malloc(sizeof(char) * strlen(term));
        strcpy(searchTerm->terms[0], term);
    }
}
