//
// Created by Thalles on 19/11/2019.
//

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dstring.h"

dString initString(dString content) {
    dString buf = malloc(sizeof(char) * (strlen(content) + 1));
    strcpy(buf, content);
    return buf;
}

void alterString(dString string, dString content) {
    string = realloc(string, sizeof(char) * (strlen(content) + 1));
    strcpy(string, content);
}

void freeString(dString string) {
    free(string);
}

dStringVector initStringVector(unsigned int size) {
    return malloc(sizeof(dString) * size);
}

void copyStringVector(dStringVector vector, unsigned int size, dStringVector content) {
    for (unsigned int i = 0; i < size; ++i) {
        alterString(vector[i], content[i]);
    }
}

void freeStringVector(dStringVector vector, unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        free(vector[i]);
    }
    free(vector);
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

void applyFuncToStrings(dStringVector vector, unsigned int size, dString (*func)(dString)) {
    for (unsigned int i = 0; i < size; ++i) {
        vector[i] = func(vector[i]);
    }
}

int countAppearances(dString string, dString token) {
    unsigned int sizeOfToken = strlen(token);
    dString positionOfToken = string;
    int i = 0;

    for (i; (positionOfToken = strstr(positionOfToken, token)) != NULL; ++i) {
        positionOfToken = positionOfToken + sizeOfToken;
    }

    i = i + 1;
    return i;
}

void explode(dString string, dString delimiter, dStringVector result) {
    dString tok;
    int i = 0;

    tok = strtok(string, delimiter);
    while (tok != NULL) {
        result[i] = initString(tok);
        tok = strtok(NULL, delimiter);
        i = i + 1;
    }
}

void implode(dStringVector vector, unsigned int size, dString glue, dString result) {
    for (unsigned int i = 0; i < size; ++i) {
        strcat(result, vector[i]);
        if ((i + 1) < size) {
            strcat(result, glue);
        }
    }
}

/*
int main(int argc, dStringVector argv){
    int size = countOccurrences(argv[1], argv[2]);
    dStringVector result = initStringVector(size);

    explode(argv[1], argv[2], result);

    for (int i = 0; i < size; ++i) {
        printf("%d:%s\n", i, result[i]);
        free(result[i]);
    }

    free(result);
}
*/
