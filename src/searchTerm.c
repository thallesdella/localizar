//
// Created by Thalles on 21/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "searchTerm.h"
#include "helpers/structs.h"

void initSearchTerm(SearchTerm *searchTerm) {
    searchTerm->count = 0;
    searchTerm->terms = malloc(sizeof(dString));
}

void addSearchTerm(SearchTerm *searchTerm, dString term) {
    searchTerm->count = splitCount(term);
    searchTerm->size = calcSearchTermSize(term);

    if (searchTerm->count > 1) {
        unsigned int sizeTerm = strlen(term);
        searchTerm->terms = realloc(searchTerm->terms, sizeof(dString) * searchTerm->count);

        for (unsigned int l = 0; l < searchTerm->count; ++l) {
            searchTerm->terms[l] = malloc(sizeof(char) * sizeTerm);
        }

        unsigned int j = 0, k = 0;
        for (unsigned int i = 0; i < sizeTerm; ++i) {
            if (term[i] == '*') {
                j = j + 1;
                k = 0;
                continue;
            }
            printf("i:%u j:%u k:%u char:%c\n", i, j, k, term[i]);
            searchTerm->terms[j][k] = term[i];
            k = k + 1;
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

int calc