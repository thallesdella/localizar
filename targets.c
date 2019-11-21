//
// Created by Thalles on 21/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "targets.h"
#include "flags.h"
#include "helpers.h"
#include "dstring.h"

int searchInTarget(dString searchTerm, dString targetPath) {
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


        dString hasString = (getFlagStatus(FLAG_CASE)
                             ? strstr(strToLower(buf), strToLower(searchTerm))
                             : strstr(buf, searchTerm));

        if (hasString != NULL) {
            occurrences = occurrences + 1;

            if (!getFlagStatus(FLAG_COUNT)) {
                if (getFlagStatus(FLAG_NUMB)) {
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

void scanDir(dString path) {
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
        addTarget(dir->d_name, dir->d_namlen);
    }
    closedir(targetDir);
}

void initTargets(Targets *initTarget) {
    initTarget->count = 0;
    initTarget->pathMaxLength = 0;
    initTarget->targets = malloc(sizeof(Target));
    initTarget->targets[0].path = malloc(sizeof(char));
}

void addTarget(dString targetPath, unsigned int targetPathLen) {
    unsigned int id = targets.count;

    targets.count = targets.count + 1;

    if (targets.count > 1) {
        targets.targets = realloc(targets.targets, sizeof(Target) * targets.count);
    }

    targetPathLen = targetPathLen + 5;
    if (targetPathLen > targets.pathMaxLength) {
        targets.pathMaxLength = targetPathLen;
        targets.targets[id].path = realloc(targets.targets[id].path, sizeof(char) * targets.pathMaxLength);
    }

    targets.targets[id].isFile = isFile(targetPath);
    targets.targets[id].isDir = isDir(targetPath);
    strcpy(targets.targets[id].path, targetPath);
}

dString getTargetPath(int id) {
    return targets.targets[id].path;
}