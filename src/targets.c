//
// Created by Thalles on 21/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "targets.h"
#include "flags.h"
#include "structs.h"
#include "helpers.h"
#include "dstring.h"

int searchInTarget(SearchTerm needle, dString targetPath, Flags flags) {
    FILE *targetFile = fopen(targetPath, "r");

    if (targetFile == NULL) {
        printf("%s:File not found", targetPath);
        return -1;
    }

    dString buf = initString("");
    int occurrences = 0, count;
    long int size = 0, oldPosition = 0;
    long int newPosition = newLinePosition(targetFile, ftell(targetFile));

    for (int line = 1; newPosition != 0; ++line) {
        size = newPosition - oldPosition;
        buf = realloc(buf, size);
        fread(buf, size, 1, targetFile);

        oldPosition = newPosition + 2;
        fgetc(targetFile);
        newPosition = newLinePosition(targetFile, oldPosition);


        if ((count = countSearchTermOccurrence(needle, buf, flags)) > 0) {
            occurrences = occurrences + count;

            if (getFlagStatus(flags, FLAG_COUNT) == 0) {
                if (getFlagStatus(flags, FLAG_NUMB)) {
                    printf("%s:%d:%s\n", targetPath, line, buf);
                } else {
                    printf("%s:%s\n", targetPath, buf);
                }
            }

            if (getFlagStatus(flags, FLAG_OUT)) {

            }
        }
    }
    freeString(buf);
    fclose(targetFile);
    return occurrences;
}

void scanDir(Targets *target, dString path) {
    DIR *targetDir = opendir(path);
    struct dirent *dir;

    if (targetDir == NULL) {
        printf("%s:Directory not found", path);
        return;
    }

    while ((dir = readdir(targetDir)) != NULL) {
        dString buf = initString(NULL);
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        sprintf(buf, "%s/%s", path, dir->d_name);
        //strcat(path, "/");
        //strcat(path, dir->d_name);
        addTarget(target, buf);

    }
    closedir(targetDir);
}

void initTargets(Targets *target) {
    target->count = 0;
    target->targets = malloc(sizeof(Target));
}

void addTarget(Targets *target, dString targetPath) {
    unsigned int id = target->count;

    target->count = target->count + 1;

    printf("addTarget - %s\n", targetPath);

    //bug
    if (target->count > 1) {
        target->targets = realloc(target->targets, sizeof(Target) * target->count);
    }

    printf("addTarget - %s\n", targetPath);

    target->targets[id].occurrences = 0;
    target->targets[id].isFile = isFile(targetPath);
    target->targets[id].isDir = isDir(targetPath);
    target->targets[id].path = initString(targetPath);

    printf("[ADD_TARGET] %s - isFile:%d isDir:%d occurrences:%d\n", target->targets[id].path,
           target->targets[id].isFile,
           target->targets[id].isDir, target->targets[id].occurrences);
}

void generateOutputFile(dString name, dString content) {
    FILE *targetFile = fopen(name, "a");
    fclose(targetFile);
}

dString getTargetPath(Targets target, unsigned int id) {
    return target.targets[id].path;
}

int countSearchTermOccurrence(SearchTerm needle, dString haystack, Flags flags) {
    int count = 0;
    dString buf = initString(haystack);

    while (verifySearchTermPresence(needle, buf, flags)) {
        count = count + 1;
    }

    freeString(buf);
    return count;
}

int verifySearchTermPresence(SearchTerm needle, dString haystack, Flags flags) {
    int testsPassed = 0;

    for (unsigned int i = 0; i < needle.count; ++i) {
        dString hasString = (!getFlagStatus(flags, FLAG_CASE)
                             ? strstr(strToLower(haystack), strToLower(needle.terms[i]))
                             : strstr(haystack, needle.terms[i]));

        if (hasString != NULL) {
            testsPassed = testsPassed + 1;
            strcpy(haystack, hasString + 1);
        }
    }

    return testsPassed == needle.count;
}