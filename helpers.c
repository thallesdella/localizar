//
// Created by THALLES on 19/11/2019.
//

##include "helpers.h"

size_t maxLength(int size, char **matrix) {
    size_t max = 0;
    for (int i = 0; i < size; ++i) {
        if (strlen(matrix[i]) > max) {
            max = strlen(matrix[i]);
        }
    }
    return max + 5;
}

void garbageCollector() {
    free(sSearchTerm);

    for (int i = 0; i < targets.count; ++i) {
        free(targets.targets[i]);
    }
    free(targets.targets);
}
