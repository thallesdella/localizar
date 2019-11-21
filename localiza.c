//
// Created by THALLES on 18/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "localiza.h"
#include "targets.h"
#include "flags.h"
#include "helpers.h"
#include "dstring.h"

void getFlagsFromArg(int argc, dStringVector argv) {
    for (int i = 0; i < flags.count; ++i) {
        checkFlagsExistence(argc, argv, &flags.flags[i]);
    };
}

void getSearchTermFromArg(dStringVector argv) {
    int searchTermPosition = flags.active + 1;
    sSearchTerm = malloc(sizeof(char) * (strlen(argv[searchTermPosition]) + 5));
    strcpy(sSearchTerm, argv[searchTermPosition]);
}

void getTargetsFromArg(int argc, dStringVector argv) {
    int initTargetPosition = flags.active + 2;
    targets.count = argc - initTargetPosition;
    targets.targets = malloc(sizeof(Target) * targets.count);

    int currentTargetPosition = initTargetPosition;
    for (size_t i = 0; i < targets.count; ++i) {
        targets.targets[i].path = malloc(sizeof(char) * maxLength(targets.count, argv));
        strcpy(targets.targets[i].path, argv[currentTargetPosition++]);
        targets.targets[i].isFile = isFile(getTargetPath(i));
        targets.targets[i].isDir = isDir(getTargetPath(i));
    }
}

void parseArguments(int argc, dStringVector argv) {
    if (argc < 3) {
        displayFlagHelp(argv[0], EXIT_FAILURE);
    }

    getFlagsFromArg(argc, argv);
    getSearchTermFromArg(argv);
    getTargetsFromArg(argc, argv);

    if (getFlagStatus(FLAG_HELP)) {
        displayFlagHelp(argv[0], EXIT_SUCCESS);
    }
}

void grep(dString searchTerm) {
    targets.totalOccurrences = 0;

    for (size_t i = 0; i < targets.count; ++i) {
        targets.targets[i].occurrences = 0;

        if (targets.targets[i].isDir) {
            scanDir();
        } else {
            int result = searchInTarget(searchTerm, getTargetPath(i));
            if (result >= 0) {
                targets.targets[i].occurrences = result;
                targets.totalOccurrences = targets.totalOccurrences + result;
            }
        }
    }
}

void garbageCollector() {
    free(sSearchTerm);

    for (size_t i = 0; i < targets.count; ++i) {
        free(&targets.targets[i]);
        free(getTargetPath(i));
    }
    free(targets.targets);
}

int main(int argc, dStringVector argv) {
    options[FLAG_HELP].status = 0;
    options[FLAG_HELP].verify = flagHelp;

    options[FLAG_CASE].status = 0;
    options[FLAG_CASE].verify = flagCaseSensitive;

    options[FLAG_COUNT].status = 0;
    options[FLAG_COUNT].verify = flagCount;

    options[FLAG_NUMB].status = 0;
    options[FLAG_NUMB].verify = flagLineNumber;

    options[FLAG_OUT].status = 0;
    options[FLAG_OUT].verify = flagOutput;

    flags.active = 0;
    flags.count = FLAGS_COUNT;
    flags.flags = options;

    parseArguments(argc, argv);

    grep(sSearchTerm);

    if (getFlagStatus(FLAG_COUNT)) {
        displayFlagCount();
    }

    garbageCollector();
    return 0;
}