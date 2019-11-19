//
// Created by THALLES on 19/11/2019.
//

#include "flags.h"

void checkFlagsExistence(int argc, char **argv, Option *flag) {
    for (int i = 1; i < argc; ++i) {
        if (flag->verify(argv[i])) {
            flag->status = 1;
            flags.active = flags.active + 1;
            return;
        }
    }
    flag->status = 0;
}

int flagHelp(String str) {
    if (strcmp(str, "-h") == 0 || strcmp(str, "--help") == 0) {
        return 1;
    }
    return 0;
}

int flagCaseSensitive(String str) {
    if (strcmp(str, "-i") == 0 || strcmp(str, "--case") == 0) {
        return 1;
    }
    return 0;
}

int flagCount(String str) {
    if (strcmp(str, "-c") == 0 || strcmp(str, "--count") == 0) {
        return 1;
    }
    return 0;
}

int flagLineNumber(String str) {
    if (strcmp(str, "-n") == 0 || strcmp(str, "--numb") == 0) {
        return 1;
    }
    return 0;
}

int flagOutput(String str) {
    if (strcmp(str, "-d") == 0 || strcmp(str, "--out") == 0) {
        return 1;
    }
    return 0;
}
