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

int explode(dString string, char delimiter, dStringVector *result) {
    dString strCopy = string, positionOfD, dst;
    dStringVector build;
    int size = 1;

    // Find number of times to explode
    while ((positionOfD = strchr(strCopy, delimiter)) != NULL) {
        ++size;
        strCopy = positionOfD + 1;
    }

    // Equivalent as the for way
    /*
     * build = malloc(size * sizeof(dString));
     * for (int i = 0; i < size; ++i){
     *  build[i] = malloc(strlen(string) + 1) * sizeof(char));
     * }
     */
    build = malloc(size * sizeof(dString) + (strlen(string) + 1) * sizeof(char));

    /*src = str;
    dst = (char *) arr + size * sizeof(char *);
    for (i = 0; i < size; ++i) {
        if ((end = strchr(src, delimiter)) == NULL)
            end = src + strlen(src);
        arr[i] = dst;
        strncpy(dst, src, end - src);
        dst[end - src] = '\0';
        dst += end - src + 1;
        src = end + 1;
    }
    *arr_ptr = arr;*/

    return size;
}
