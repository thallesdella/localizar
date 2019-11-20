//
// Created by THALLES on 19/11/2019.
//

#include <string.h>
#include <stdlib.h>
#include "helpers.h"

size_t maxLength(int size, char **matrix) {
    size_t max = 0;
    for (int i = 0; i < size; ++i) {
        if (strlen(matrix[i]) > max) {
            max = strlen(matrix[i]);
        }
    }
    return max + 5;
}
