//
// Created by Thalles on 21/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "targets.h"
#include "flags.h"
#include "helpers/structs.h"
#include "helpers/helpers.h"
#include "helpers/dstring.h"

int searchInTarget(Flags flags, SearchTerm searchTerm, dString targetPath) {
    FILE *targetFile = fopen(targetPath, "r");

    if (targetFile == NULL) {
        printf("%s:File not found", targetPath);
        return -1;
    }

    dString buf = malloc(sizeof(char));
    int occurrences = 0;
    long int size = 0, oldPosition = 0;
    long int newPosition = newLinePosition(targetFile, ftell(targetFile));

    for (int line = 1; newPosition != 0; ++line) {
        size = newPosition - oldPosition;
        buf = realloc(buf, size);
        fread(buf, size, 1, targetFile);

        oldPosition = newPosition + 2;
        fgetc(targetFile);
        newPosition = newLinePosition(targetFile, oldPosition);

        int testsPassed = 0;
        for (unsigned int i = 0; i < searchTerm.count; ++i) {
            dString hasString = (!getFlagStatus(flags, FLAG_CASE)
                                 ? strstr(strToLower(buf), strToLower(searchTerm.terms[i]))
                                 : strstr(buf, searchTerm.terms[i]));
            if (hasString != NULL) {
                testsPassed = testsPassed + 1;
            }
        }

        if (testsPassed == searchTerm.count) {
            occurrences = occurrences + 1;

            if (!getFlagStatus(flags, FLAG_COUNT)) {
                if (getFlagStatus(flags, FLAG_NUMB)) {
                    printf("%s:%d:%s", targetPath, line, buf);
                } else {
                    printf("%s:%s", targetPath, buf);
                }
            }
        }
    }
    free(buf);
    fclose(targetFile);
    return occurrences;
}

void scanDir(Targets *target, dString path) {
    DIR *targetDir = opendir(path);
    struct dirent *dir;

    if (targetDir == NULL) {
        printf("%s:File not found", path);
        return;
    }

    while ((dir = readdir(targetDir)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }
        addTarget(target, dir->d_name, dir->d_namlen);
    }
    closedir(targetDir);
}

void initTargets(Targets *target) {
    target->count = 0;
    target->pathMaxLength = 0;
    target->targets = malloc(sizeof(Target));
    target->targets[0].path = malloc(sizeof(char));
}

void addTarget(Targets *target, dString targetPath, unsigned int targetPathLen) {
    unsigned int id = target->count;

    target->count = target->count + 1;

    if (target->count > 1) {
        target->targets = realloc(target->targets, sizeof(Target) * target->count);
    }

    targetPathLen = targetPathLen + 5;
    if (targetPathLen > target->pathMaxLength) {
        target->pathMaxLength = targetPathLen;
        target->targets[id].path = realloc(target->targets[id].path, sizeof(char) * target->pathMaxLength);
    }

    target->targets[id].isFile = isFile(targetPath);
    target->targets[id].isDir = isDir(targetPath);
    strcpy(target->targets[id].path, targetPath);
}

dString getTargetPath(Targets target, unsigned int id) {
    return target.targets[id].path;
}