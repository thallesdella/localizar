//
// Created by THALLES on 18/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "localiza.h"

void help(const char *scriptname) {
    printf("-- MODO DE USO --\n");
    printf("\t./%s <params> search <files|directories>\n\n", scriptname);
    printf("-- HELP --\n");
    printf("\t-h --help\t- Display help\n");
    printf("\t-i --case\t- Case sensitive search disable\n");
    printf("\t-c --count\t- Count apperances\n");
    printf("\t-n --numb\t- Display line number\n");
    printf("\t-d --out\t- Save an output copy without the search term\n");

    exit(EXIT_SUCCESS);
}

int checkFlagsExistence(int argc, char **argv, const char *sFlags) {
    for (int j = 1; j < argc; ++j) {
        if (strcmp(argv[j], sFlags) == 0) {
            return 1;
        }
    }
    return 0;
}

int flagHelp(int argc, char **argv) {
    if (checkFlagsExistence(argc, argv, "-h") || checkFlagsExistence(argc, argv, "--help")) {
        return 1;
    }
    return 0;
}

int flagCaseSensitive(int argc, char **argv) {
    if (checkFlagsExistence(argc, argv, "-i") || checkFlagsExistence(argc, argv, "--case")) {
        return 1;
    }
    return 0;
}

int flagCount(int argc, char **argv) {
    if (checkFlagsExistence(argc, argv, "-c") || checkFlagsExistence(argc, argv, "--count")) {
        return 1;
    }
    return 0;
}

int flagLineNumber(int argc, char **argv) {
    if (checkFlagsExistence(argc, argv, "-n") || checkFlagsExistence(argc, argv, "--numb")) {
        return 1;
    }
    return 0;
}

int flagOutput(int argc, char **argv) {
    if (checkFlagsExistence(argc, argv, "-d") || checkFlagsExistence(argc, argv, "--out")) {
        return 1;
    }
    return 0;
}

void getFlagsFromArg(int argc, char **argv) {
    flags.help = flagHelp(argc, argv);
    flags.sensitive = flagCaseSensitive(argc, argv);
    flags.count = flagCount(argc, argv);
    flags.line = flagLineNumber(argc, argv);
    flags.out = flagOutput(argc, argv);

    flags.active = flags.help + flags.sensitive + flags.count + flags.line + flags.out;
}

void getSearchTermFromArg(char **argv) {
    int searchTermPosition = flags.active + 1;
    sSearchTerm = malloc((strlen(argv[searchTermPosition]) + 10));
    strcpy(sSearchTerm, argv[searchTermPosition]);
}

void getTargetsFromArg(int argc, int **argv) {
    int countTargets = argc - flags.active;
    int searchTargetPosition = flags.active + 2;
    aTargets = malloc(sizeof(char *) * countTargets);

    for (int i = 0; i < countTargets; ++i) {
        aTargets[i] =
    }
}

int main(int argc, char **argv) {
    getFlagsFromArg(argc, argv);

    if (argc < 3 || flags.help) {
        help(argv[0]);
    }

    getSearchTermFromArg(argv);

    free(sSearchTerm);
}
