//
// Created by Thalles on 19/11/2019.
//

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dstring.h"

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

int countAppearances(dString string, dString token) {
    unsigned int sizeOfToken = strlen(token);
    dString positionOfToken = string;
    int i = 0;

    for (i; (positionOfD = strstr(positionOfToken, token)) != NULL; ++i) {
        positionOfD = positionOfD + sizeOfToken;
    }
    i = i + 1;

    return i;
}

void explode(dString string, dString delimiter, dStringVector result) {
    dString tok;
    int i = 0;

    tok = strtok (string, delimiter);
    while (tok != NULL) {
        result[i] = malloc(sizeof(char) * strlen(tok));
        strcpy(result[i], tok);
        printf("%s - %s\n", tok, result[i]);
        tok = strtok (NULL, delimiter);
        i = i + 1;
    }
}

/*

typedef char * dString;
typedef char ** dStringVector;

int countOccurrences(dString string, dString delimiter){
    unsigned int sizeOfDelimiter = strlen(delimiter);
    dString positionOfD = string;
    int i = 0;

    for (i; (positionOfD = strstr(positionOfD, delimiter)) != NULL; ++i) {
        positionOfD = positionOfD + sizeOfDelimiter;
    }
    i = i + 1;

    return i;
}

void explode(dString string, dString delimiter, dStringVector result){
    dString tok;
    int i = 0;

    tok = strtok (string, delimiter);
    while (tok != NULL) {
        result[i] = malloc(sizeof(char) * strlen(tok));
        strcpy(result[i], tok);
        printf("%s - %s\n", tok, result[i]);
        tok = strtok (NULL, delimiter);
        i = i + 1;
    }
}

int main(int argc, dStringVector argv){
    int size = countOccurrences(argv[1], argv[2]);
    dStringVector result = malloc(sizeof(dString) * size);

    explode(argv[1], argv[2], result);

    for (int i = 0; i < size; ++i) {
        printf("%d:%s\n", i, result[i]);
        free(result[i]);
    }

    free(result);
}

*/
