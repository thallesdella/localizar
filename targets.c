//
// Created by Thalles on 21/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "targets.h"
#include "flags.h"
#include "helpers.h"
#include "dstring.h"

int isFile(dString path) {
    Stat statBuf;
    stat(path, &statBuf);
    return S_ISREG(statBuf.st_mode);
}

int isDir(dString path) {
    Stat statBuf;
    if (stat(path, &statBuf) != 0) {
        return 0;
    }
    return S_ISDIR(statBuf.st_mode);
}

dString getTargetPath(int id) {
    return targets.targets[id].path;
}

void scanDir(dString path) {
    DIR *d = opendir(path);
    struct dirent *dir;

    if (d != NULL) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
                continue;
            }

            unsigned int id = targets.count;
            unsigned int size = maxLengthTargetPath(dir->d_name);

            targets.count = targets.count + 1;
            targets.targets = realloc(targets.targets, sizeof(Target) * targets.count);
            targets.targets[id].path = realloc(targets.targets[id].path, sizeof(char) * size);
            targets.targets[id].isFile = isFile(dir->d_name);
            targets.targets[id].isDir = isDir(dir->d_name);
            strcpy(targets.targets[id].path, dir->d_name);
        }
        closedir(d);
    }
}

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