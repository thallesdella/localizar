//
// Created by THALLES on 19/11/2019.
//

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "helpers.h"
#include "dstring.h"

size_t maxLength(int size, dStringVector matrix) {
    size_t max = 0;
    for (int i = 0; i < size; ++i) {
        if (strlen(matrix[i]) > max) {
            max = strlen(matrix[i]);
        }
    }
    return max + 5;
}

dString strToLower(dString string) {
    for (size_t i = 0; i < strlen(string); ++i) {
        string[i] = (char) tolower((int) string[i]);
    }
    return string;
}

dString strToUpper(dString string) {
    for (size_t i = 0; i < strlen(string); ++i) {
        string[i] = (char) toupper((int) string[i]);
    }
    return string;
}
