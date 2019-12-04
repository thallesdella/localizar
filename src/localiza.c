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
#include "helpers.h"

int isDebug() {
    return getFlagStatus(flags, FLAG_DEBUG);
}

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
    //targets.totalOccurrences = 0;

    for (unsigned int i = 0; i < targets.count; ++i) {
        //targets.targets[i].occurrences = 0;

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

            int *result = searchInTarget(searchTerm, getTargetPath(targets, i), flags);
            if (result[0] == 0) {
                if (result[1] == 0) {
                    printMsgForFile(targets, i, "Didnt find any occurrences");
                }

                targets.targets[i].hotLines = result[1];
                targets.targets[i].occurrences = result[2];
                targets.totalHotLines = targets.totalHotLines + result[1];
                targets.totalOccurrences = targets.totalOccurrences + result[2];
            }
            free(result);
        } else {
            printMsgForFile(targets, i, "File or directory dont exists");
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
    superGlobal.isDebug = isDebug;
    printDebugMsg(" -- Debug Mode On -- ");

    VecFlagsFunc verifyFlags[FLAGS_COUNT] = {flagHelp, flagCaseSensitive, flagCount, flagLineNumber,
                                             flagOutput, flagDebug};
    options = malloc(sizeof(Option) * FLAGS_COUNT);

    initFlags(&flags, options, verifyFlags, FLAGS_COUNT);
    initSearchTerm(&searchTerm);
    initTargets(&targets);
    printDebugMsg("[MAIN] Finish Init");

    parseArguments(argc, argv);
    printDebugMsg("[MAIN] Finish argument parse");

    grep();

    if (getFlagStatus(flags, FLAG_COUNT) == 1) {
        displayFlagCount(targets);
    }
    printDebugMsg("[MAIN] Finish grep");

    garbageCollector();
    printDebugMsg("[MAIN] Cleaning the dirt");

    return 0;
}
