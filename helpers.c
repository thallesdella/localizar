//
// Created by THALLES on 19/11/2019.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include "helpers.h"
#include "dstring.h"
#include "targets.h"

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

int isFile(dString path) {
    Stat statBuf;
    stat(path, &statBuf);
    return S_ISREG(statBuf.st_mode);
}

int isDir(dString path) {
    Stat statBuf;
    if (stat(path, &statBuf) != 0) {
        return 0;
    }
    return S_ISDIR(statBuf.st_mode);
}