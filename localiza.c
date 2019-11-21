//
// Created by THALLES on 18/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "localiza.h"
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

int newLinePosition(FILE *stream, long int start) {
    int c = 0, i = 0;
    while (c != '\n' && !feof(stream)) {
        i = ftell(stream);
        c = fgetc(stream);
    }
    fseek(stream, start, SEEK_SET);
    return i;
}

void grep(dString searchTerm) {
    dString buf = malloc(sizeof(char));
    FILE *targetFile;
    targets.totalOccurrences = 0;

    for (size_t i = 0; i < targets.count; ++i) {
        targets.targets[i].occurrences = 0;
        targetFile = fopen(targets.targets[i].path, "r");

        if (targetFile == NULL) {
            printf("%s:File not found", targets.targets[i].path);
            continue;
        }

        long int size = 0, oldPosition = 0;
        long int newPosition = newLinePosition(targetFile, ftell(targetFile));

        for (int line = 1; newPosition != 0; ++line) {
            size = newPosition - oldPosition;
            buf = realloc(buf, size);
            fread(buf, size, 1, targetFile);

            oldPosition = newPosition + 2;
            fgetc(targetFile);
            newPosition = newLinePosition(targetFile, oldPosition);


            dString hasString = (getFlagStatus(FLAG_CASE)
                                 ? strstr(strToLower(buf), strToLower(searchTerm))
                                 : strstr(buf, searchTerm));

            if (hasString != NULL) {
                targets.totalOccurrences = targets.totalOccurrences + 1;
                targets.targets[i].occurrences = targets.targets[i].occurrences + 1;

                if (!getFlagStatus(FLAG_COUNT)) {
                    if (getFlagStatus(FLAG_NUMB)) {
                        printf("%s:%d:%s", targets.targets[i].path, line, buf);
                    } else {
                        printf("%s:%s", targets.targets[i].path, buf);
                    }
                }
            }
        }
        fclose(targetFile);
    }
    free(buf);
}

void garbageCollector() {
    free(sSearchTerm);

    for (size_t i = 0; i < targets.count; ++i) {
        free(&targets.targets[i]);
        free(targets.targets[i].path);
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
