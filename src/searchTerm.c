//
// Created by Thalles on 21/11/2019.
//

#include <stdlib.h>
#include <string.h>
#include "searchTerm.h"
#include "helpers/structs.h"

void initSearchTerm(SearchTerm *searchTerm) {
    searchTerm->count = 0;
    searchTerm->terms = malloc(sizeof(dString));
    searchTerm->terms[0] = malloc(sizeof(char));
}

void addSearchTerm(SearchTerm *searchTerm, dString term) {
    searchTerm->count = splitCount(term);

    if (searchTerm->count > 1) {
        unsigned int id = 0;
        searchTerm->terms = realloc(searchTerm->terms, sizeof(dString) * searchTerm->count);
        dString buf;

        while ((buf = strtok(term, "*")) != NULL) {
            searchTerm->terms[id] = malloc(sizeof(char) * strlen(buf));
            strcpy(searchTerm->terms[id], buf);
            id = id + 1;
        }
    } else {
        searchTerm->count = 1;
        searchTerm->terms[0] = malloc(sizeof(char) * strlen(term));
        strcpy(searchTerm->terms[0], term);
    }
}

int splitCount(dString term) {
    int occurrences = 0;
    for (unsigned int i = 0; i < strlen(term); ++i) {
        if (term[i] == '*') {
            occurrences = occurrences + 1;
        }
    }
    return occurrences + 1;
}