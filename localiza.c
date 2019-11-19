//
// Created by THALLES on 18/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "localiza.h"

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

size_t maxLength(int size, char **matrix) {
    size_t max = 0;
    for (int i = 0; i < size; ++i) {
        if (strlen(matrix[i]) > max) {
            max = strlen(matrix[i]);
        }
    }
    return max + 5;
}

void getFlagsFromArg(int argc, char **argv) {
    for (int i = 0; i < flags.count; ++i) {
        checkFlagsExistence(argc, argv, &flags.flags[i]);
    };
}

void getSearchTermFromArg(char **argv) {
    int searchTermPosition = flags.active + 1;
    sSearchTerm = malloc(sizeof(char) * (strlen(argv[searchTermPosition]) + 5));
    strcpy(sSearchTerm, argv[searchTermPosition]);
}

void getTargetsFromArg(int argc, char **argv) {
    int initTargetPosition = flags.active + 2;
    targets.count = argc - initTargetPosition;
    targets.targets = malloc(sizeof(String) * targets.count);

    int currentTargetPosition = initTargetPosition;
    for (int i = 0; i < targets.count; ++i) {
        targets.targets[i] = malloc(sizeof(char) * maxLength(targets.count, argv));
        strcpy(targets.targets[i], argv[currentTargetPosition++]);
    }
}

void parseArguments(int argc, char **argv) {
    if (argc < 3) {
        help(argv[0], EXIT_FAILURE);
    }

    getFlagsFromArg(argc, argv);
    getSearchTermFromArg(argv);
    getTargetsFromArg(argc, argv);

    if (flags.flags[FLAG_HELP].status) {
        help(argv[0], EXIT_SUCCESS);
    }
}

void garbageCollector() {
    free(sSearchTerm);

    for (int i = 0; i < targets.count; ++i) {
        free(targets.targets[i]);
    }
    free(targets.targets);
}

void help(String scriptname, int exitCode) {
    printf("-- USAGE --\n");
    printf("\t./%s [option... | null] [pattern] [file...]>\n", scriptname);
    printf("\t./%s \"jesus\" bible.txt>\n\n", scriptname);
    printf("-- HELP --\n");
    printf("\t-h --help\t- Display help\n");
    printf("\t-i --case\t- Case sensitive search disable\n");
    printf("\t-c --count\t- Count apperances\n");
    printf("\t-n --numb\t- Display line number\n");
    printf("\t-d --out\t- Save an output copy without the search term\n");

    exit(exitCode);
}

void grep(String searchTerm) {
    String buf = malloc(sizeof(char) * BUFSIZ);
    FILE *targetFile;
    for (int i = 0; i < targets.count; ++i) {
        targetFile = fopen(targets.targets[i], "r");

        if (targetFile == NULL) {
            printf("%s:File not found", targets.targets[i]);
            continue;
        }

        while (fgets(buf, BUFSIZ, targetFile) != NULL) {
            if (strstr(searchTerm, buf) != NULL) {
                printf("%s:%s", targets.targets[i], buf);
            }
        }
        fclose(targetFile);
    }
    free(buf);
}

int main(int argc, char **argv) {
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
