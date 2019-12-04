//
// Created by THALLES on 19/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flags.h"
#include "structs.h"
#include "dstring.h"

void initFlags(Flags *structFlags, Option *arrStructOption, VecFlagsFunc *func, int flagsCount) {
    for (int i = 0; i < flagsCount; ++i) {
        arrStructOption[i].status = 0;
        arrStructOption[i].verify = func[i];
    }

    structFlags->active = 0;
    structFlags->count = flagsCount;
    structFlags->flags = arrStructOption;
}

void displayFlagHelp(dString scriptName, int exitCode) {
    printf("-- USAGE --\n");
    printf("\t./%s [null|flags...] [pattern] [file|dir...]\n", scriptName);
    printf("\t./%s jesus bible.txt all-bibles-in-the-world\n\n", scriptName);
    printf("-- FLAGS --\n");
    printf("\t-h --help\t - Display help\n");
    printf("\t-i --case\t - Case sensitive search disable\n");
    printf("\t-c --count\t - Display count of lines with has appearances of the pattern\n");
    //printf("\t-o --time\t - Display occurrences os the pattern in the file\n");
    printf("\t-n --numb\t - Display line number witch contains the pattern \n");
    printf("\t-d --out\t - Save an output copy without the pattern\n");

    exit(exitCode);
}

void displayFlagCount(Targets target) {
    printf("OCCURRENCES: \n");

    for (unsigned int i = 0; i < target.count; ++i) {
        if (target.targets[i].isFile) {
            printf("\t%s:%u %s\n", target.targets[i].path, target.targets[i].occurrences,
                   (target.targets[i].occurrences > 1 ? "founds" : "found"));
        }
    }

    if (target.count > 1) {
        printf("TOTAL:%u %s\n", target.totalOccurrences, (target.totalOccurrences > 1 ? "founds" : "found"));
    }
}

void checkFlagsExistence(Flags *flags, Option *option, int argc, dStringVector argv) {
    for (int i = 1; i < argc; ++i) {
        if (option->verify(argv[i])) {
            option->status = 1;
            flags->active = flags->active + 1;

            if (superGlobal.isDebug()) {
                printf("[FLAGS] %s status:active", argv[i]);
            }
            return;
        }
    }
}

int getFlagStatus(Flags flags, int id) {
    return flags.flags[id].status;
}

int flagDebug(dString str) {
    if (strcmp(str, "--debug") == 0) {
        return 1;
    }
    return 0;
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

int flagOccurrences(dString str) {
    if (strcmp(str, "-o") == 0 || strcmp(str, "--time") == 0) {
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