//
// Created by THALLES on 19/11/2019.
//

#include <string.h>
#include "flags.h"

void checkFlagsExistence(int argc, dStringVector argv, Option *flag) {
    for (int i = 1; i < argc; ++i) {
        if (flag->verify(argv[i])) {
            flag->status = 1;
            flags.active = flags.active + 1;
            return;
        }
    }
    flag->status = 0;
}

int getFlagStatus(int id) {
    return flags.flags[id].status;
}

int flagHelp(dString str) {
    if (strcmp(str, "-h") == 0 || strcmp(str, "--help") == 0) {
        return 1;
    }
    return 0;
}

int flagCaseSensitive(dString str) {
    if (strcmp(str, "-i") == 0 || strcmp(str, "--case") == 0) {
        return 1;
    }
    return 0;
}

int flagCount(dString str) {
    if (strcmp(str, "-c") == 0 || strcmp(str, "--count") == 0) {
        return 1;
    }
    return 0;
}

int flagLineNumber(dString str) {
    if (strcmp(str, "-n") == 0 || strcmp(str, "--numb") == 0) {
        return 1;
    }
    return 0;
}

int flagOutput(dString str) {
    if (strcmp(str, "-d") == 0 || strcmp(str, "--out") == 0) {
        return 1;
    }
    return 0;
}
