//
// Created by THALLES on 18/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "targets.h"
#include "flags.h"
#include "searchTerm.h"
#include "helpers/structs.h"
#include "helpers/dstring.h"

void getFlagsFromArg(int argc, dStringVector argv) {
    for (unsigned int i = 0; i < flags.count; ++i) {
        checkFlagsExistence(&flags, &flags.flags[i], argc, argv);
    }
}

void getSearchTermFromArg(dStringVector argv) {
    unsigned int searchTermPosition = flags.active + 1;
    addSearchTerm(&searchTerm, argv[searchTermPosition]);
}

void getTargetsFromArg(int argc, dStringVector argv) {
    unsigned int initTargetPosition = flags.active + 2;
    unsigned int currentTargetPosition = initTargetPosition;
    unsigned int targetsCount = argc - initTargetPosition;

    for (unsigned int i = 0; i < targetsCount; ++i) {
        addTarget(&targets, argv[currentTargetPosition], strlen(argv[currentTargetPosition]));
        currentTargetPosition = currentTargetPosition + 1;
    }
}

void parseArguments(int argc, dStringVector argv) {
    getFlagsFromArg(argc, argv);

    if (getFlagStatus(flags, FLAG_HELP)) {
        displayFlagHelp(argv[0], EXIT_SUCCESS);
    }

    if (argc < 3) {
        displayFlagHelp(argv[0], EXIT_FAILURE);
    }

    getSearchTermFromArg(argv);
    getTargetsFromArg(argc, argv);
}

void grep(void) {
    targets.totalOccurrences = 0;

    for (size_t i = 0; i < targets.count; ++i) {
        targets.targets[i].occurrences = 0;

        if (targets.targets[i].isDir) {
            scanDir(&targets, getTargetPath(targets, i));
        } else {
            int result = searchInTarget(flags, searchTerm, getTargetPath(targets, i));
            if (result >= 0) {
                targets.targets[i].occurrences = result;
                targets.totalOccurrences = targets.totalOccurrences + result;
            }
        }
    }
}

void garbageCollector() {
    free(options);

    for (unsigned int i = 0; i < targets.count; ++i) {
        free(getTargetPath(targets, i));
    }
    free(targets.targets);
}

int main(int argc, dStringVector argv) {
    Vflags verifyFlags[FLAGS_COUNT] = {flagHelp, flagCaseSensitive, flagCount, flagLineNumber, flagOutput};
    options = malloc(sizeof(Option) * FLAGS_COUNT);
    initFlags(&flags, options, verifyFlags, FLAGS_COUNT);

    initSearchTerm(&searchTerm);

    initTargets(&targets);

    parseArguments(argc, argv);

    printf("search:%d\n", searchTerm.count);
    for (int i = 0; i < searchTerm.count; ++i) {
        printf("%s\n", searchTerm.terms[i]);
    }

    grep();

    if (getFlagStatus(flags, FLAG_COUNT)) {
        displayFlagCount(targets);
    }

    garbageCollector();
    return 0;
}
