//
// Created by THALLES on 18/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "localiza.h"
#include "targets.h"
#include "flags.h"
#include "searchTerm.h"
#include "structs.h"
#include "dstring.h"

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
        addTarget(&targets, argv[currentTargetPosition]);
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

    for (unsigned int i = 0; i < targets.count; ++i) {
        targets.targets[i].occurrences = 0;

        if (targets.targets[i].isDir) {
            scanDir(&targets, getTargetPath(targets, i));
        } else if (targets.targets[i].isFile) {
            if (getFlagStatus(flags, FLAG_COUNT) == 0) {
                if (i != 0) {
                    printf("\n");
                }

                dString pathCopy = initString(getTargetPath(targets, i));
                printf("-- %s:\n", strToUpper(pathCopy));
                freeString(pathCopy);
            }

            int result = searchInTarget(searchTerm, getTargetPath(targets, i), flags);
            if (result >= 0) {
                targets.targets[i].occurrences = result;
                targets.totalOccurrences = targets.totalOccurrences + result;
            }
        } else {
            printf("%s:File or directory dont exist\n", getTargetPath(targets, i));
        }
    }
}

void garbageCollector() {
    free(options);

    freeStringVector(searchTerm.terms, searchTerm.count);

    for (unsigned int i = 0; i < targets.count; ++i) {
        free(getTargetPath(targets, i));
    }
    free(targets.targets);
}

int main(int argc, dStringVector argv) {
    VecFlagsFunc verifyFlags[FLAGS_COUNT] = {flagHelp, flagCaseSensitive, flagCount, flagLineNumber,
                                             flagOutput, flagDebug};
    options = malloc(sizeof(Option) * FLAGS_COUNT);
    initFlags(&flags, options, verifyFlags, FLAGS_COUNT);

    initSearchTerm(&searchTerm);

    initTargets(&targets);

    parseArguments(argc, argv);

    grep();

    if (getFlagStatus(flags, FLAG_COUNT) == 1) {
        displayFlagCount(targets);
    }

    garbageCollector();
    return 0;
}
