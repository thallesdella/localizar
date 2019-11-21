//
// Created by THALLES on 19/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flags.h"
#include "targets.h"

void displayFlagHelp(dString scriptName, int exitCode) {
    printf("-- USAGE --\n");
    printf("\t./%s [option... | null] [pattern] [file...]\n", scriptName);
    printf("\t./%s jesus bible.txt\n\n", scriptName);
    printf("-- HELP --\n");
    printf("\t-h --help\t- Display help\n");
    printf("\t-i --case\t- Case sensitive search disable\n");
    printf("\t-c --count\t- Count apperances\n");
    printf("\t-n --numb\t- Display line number\n");
    printf("\t-d --out\t- Save an output copy without the search term\n");

    exit(exitCode);
}

void displayFlagCount(void) {
    printf("OCCURRENCES: \n");

    for (size_t i = 0; i < targets.count; ++i) {
        printf("\t%s:%u %s\n", targets.targets[i].path, targets.targets[i].occurrences,
               (targets.targets[i].occurrences > 1 ? "founds" : "found"));
    }

    if (targets.count > 1) {
        printf("TOTAL:%u %s\n", targets.totalOccurrences, (targets.totalOccurrences > 1 ? "founds" : "found"));
    }
}

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