//
// Created by THALLES on 18/11/2019.
//

#include <stdlib.h>
#include <string.h>
#include "localiza.h"
#include "targets.h"
#include "flags.h"
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
    int currentTargetPosition = initTargetPosition;
    int targetsCount = argc - initTargetPosition;

    for (unsigned int i = 0; i < targetsCount; ++i) {
        addTarget(argv[currentTargetPosition], strlen(argv[currentTargetPosition]));
        currentTargetPosition = currentTargetPosition + 1;
    }
}

void parseArguments(int argc, dStringVector argv) {
    getFlagsFromArg(argc, argv);

    if (getFlagStatus(FLAG_HELP)) {
        displayFlagHelp(argv[0], EXIT_SUCCESS);
    }

    if (argc < 3) {
        displayFlagHelp(argv[0], EXIT_FAILURE);
    }

    getSearchTermFromArg(argv);
    getTargetsFromArg(argc, argv);
}

void grep(dString searchTerm) {
    targets.totalOccurrences = 0;

    for (size_t i = 0; i < targets.count; ++i) {
        targets.targets[i].occurrences = 0;

        if (targets.targets[i].isDir) {
            scanDir(getTargetPath(i));
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
    free(options);
    free(sSearchTerm);

    for (unsigned int i = 0; i < targets.count; ++i) {
        free(getTargetPath(i));
    }
    free(targets.targets);
}

int main(int argc, dStringVector argv) {
    Vflags verifyFlags[FLAGS_COUNT] = {flagHelp, flagCaseSensitive, flagCount, flagLineNumber, flagOutput};
    options = malloc(sizeof(Option) * FLAGS_COUNT);
    initFlags(&flags, options, verifyFlags, FLAGS_COUNT);

    initTargets(&targets);

    parseArguments(argc, argv);

    grep(sSearchTerm);

    if (getFlagStatus(FLAG_COUNT)) {
        displayFlagCount(targets);
    }

    garbageCollector();
    return 0;
}