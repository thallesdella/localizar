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
    targets.targets = malloc(sizeof(dString) * targets.count);

    int currentTargetPosition = initTargetPosition;
    for (int i = 0; i < targets.count; ++i) {
        targets.targets[i] = malloc(sizeof(char) * maxLength(targets.count, argv));
        strcpy(targets.targets[i], argv[currentTargetPosition++]);
    }
}

void parseArguments(int argc, dStringVector argv) {
    if (argc < 3) {
        help(argv[0], EXIT_FAILURE);
    }

    getFlagsFromArg(argc, argv);
    getSearchTermFromArg(argv);
    getTargetsFromArg(argc, argv);

    if (getFlagStatus(FLAG_HELP)) {
        help(argv[0], EXIT_SUCCESS);
    }
}

void help(dString scriptname, int exitCode) {
    printf("-- USAGE --\n");
    printf("\t./%s [option... | null] [pattern] [file...]\n", scriptname);
    printf("\t./%s jesus bible.txt\n\n", scriptname);
    printf("-- HELP --\n");
    printf("\t-h --help\t- Display help\n");
    printf("\t-i --case\t- Case sensitive search disable\n");
    printf("\t-c --count\t- Count apperances\n");
    printf("\t-n --numb\t- Display line number\n");
    printf("\t-d --out\t- Save an output copy without the search term\n");

    exit(exitCode);
}

int newLinePosition(FILE *stream, long int start) {
    int c = 0, i = 0;
    while (c != '\n' && !feof(stream)) {
        i = ftell(stream);
        c = fgetc(stream);
        //printf("char:%c - position:%d\n", c, i);
    }
    fseek(stream, start, SEEK_SET);
    return i;
}

void grep(dString searchTerm) {
    dString buf = malloc(sizeof(char));
    FILE *targetFile;
    for (int i = 0; i < targets.count; ++i) {
        targetFile = fopen(targets.targets[i], "r");

        if (targetFile == NULL) {
            printf("%s:File not found", targets.targets[i]);
            continue;
        }

        long int oldPosition = 0, newPosition = newLinePosition(targetFile, ftell(targetFile));
        long int size = newPosition - oldPosition;
        for (int line = 1; newPosition != 0; ++line) {
            size = newPosition - oldPosition;
            buf = realloc(buf, size);
            fread(buf, size, 1, targetFile);

            oldPosition = newPosition + 2;
            fgetc(targetFile);
            newPosition = newLinePosition(targetFile, oldPosition);

            if (strstr(buf, searchTerm) != NULL) {
                if (getFlagStatus(FLAG_NUMB)) {
                    printf("%s:%d:%s", targets.targets[i], line, buf);
                }else{
                    printf("%s:%s", targets.targets[i], buf);
                }
            }
        }
        fclose(targetFile);
    }
    free(buf);
}

void garbageCollector() {
    free(sSearchTerm);

    for (int i = 0; i < targets.count; ++i) {
        free(targets.targets[i]);
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

    /*printf("Flags:\nhelp:%d case:%d count:%d line:%d out:%d - active:%d\n", flags.flags[FLAG_HELP].status,
           flags.flags[FLAG_CASE].status, flags.flags[FLAG_COUNT].status, flags.flags[FLAG_NUMB].status,
           flags.flags[FLAG_OUT].status, flags.active);

    printf("Search: %s\n", sSearchTerm);

    printf("targets:\n");
    for (int i = 0; i < targets.count; ++i) {
        printf("%s\n", targets.targets[i]);
    }*/

    garbageCollector();
    return 0;
}
