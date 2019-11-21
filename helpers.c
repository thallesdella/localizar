//
// Created by THALLES on 19/11/2019.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "helpers.h"
#include "dstring.h"
#include "targets.h"

unsigned int maxLength(unsigned int size, dStringVector matrix) {
    size_t max = 0, len;
    for (unsigned int i = 0; i < size; ++i) {
        len = strlen(matrix[i]);
        if (len > max) {
            max = len;
        }
    }
    return max + 5;
}

unsigned int maxLengthTargetPath(dString newPath) {
    size_t max = 0, len;
    for (unsigned int i = 0; i < targets.count; ++i) {
        len = strlen(targets.targets[i].path);
        if (len > max) {
            max = len;
        }
    }

    len = strlen(newPath);
    if (len > max) {
        return len + 5;
    }
    return max + 5;
}

int newLinePosition(FILE *stream, long int start) {
    int c = 0, i = 0;
    while (c != '\n' && !feof(stream)) {
        i = ftell(stream);
        c = fgetc(stream);
    }
    fseek(stream, start, SEEK_SET);
    return i;
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
