//
// Created by Thalles on 21/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "targets.h"
#include "flags.h"
#include "searchTerm.h"
#include "structs.h"
#include "helpers.h"
#include "dstring.h"

int *searchInTarget(SearchTerm needle, dString targetPath, Flags flags) {
    FILE *targetFile = fopen(targetPath, "r");

    if (targetFile == NULL) {
        printf("%s:File not found", targetPath);
        return -1;
    }

    dString buf = initString(NULL);
    int count, *occurrences = malloc(sizeof(int) * 2);
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
            occurrences[0] = occurrences[0] + 1;
            occurrences[1] = occurrences[1] + count;

            if (getFlagStatus(flags, FLAG_COUNT) == 0) {
                if (getFlagStatus(flags, FLAG_NUMB)) {
                    printf("%s:%d:%s\n", targetPath, line, buf);
                } else {
                    printf("%s:%s\n", targetPath, buf);
                }
            }

            if (getFlagStatus(flags, FLAG_OUT)) {
                dString cleanStr = initString(buf);
                removeSearchTermFromLine(cleanStr, needle);
                generateOutputFile(targetPath, cleanStr);
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
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        dString buf = initString(path);
        concatStr(buf, 2, "/", dir->d_name);

        addTarget(target, buf);
        freeString(buf);
    }
    closedir(targetDir);
}

void initTargets(Targets *target) {
    target->count = 0;
    target->totalHotLines = 0;
    target->totalOccurrences = 0;
    target->targets = malloc(sizeof(Target));
}

void addTarget(Targets *target, dString targetPath) {
    unsigned int id = target->count;

    target->count = target->count + 1;

    if (target->count > 1) {
        target->targets = realloc(target->targets, sizeof(Target) * target->count);
    }

    target->targets[id].occurrences = 0;
    target->targets[id].hotLines = 0;
    target->targets[id].isFile = isFile(targetPath);
    target->targets[id].isDir = isDir(targetPath);
    target->targets[id].path = initString(targetPath);


    if (superGlobal.isDebug()) {
        printf("[ADD_TARGET] %s - isFile:%d isDir:%d occurrences:%d\n", target->targets[id].path,
               target->targets[id].isFile,
               target->targets[id].isDir, target->targets[id].occurrences);
    }
}

void generateOutputFile(dString name, dString content) {
    dString buf = initString(name);
    generateName(buf);

    FILE *targetFile = fopen(buf, "a");

    if (targetFile == NULL) {
        printf("%s: Unable to open file.\n", buf);
        return;
    }

    fputs(content, targetFile);
    fclose(targetFile);
}


void generateName(dString baseName) {
    dString buf = initString(baseName);
    int count = countAppearances(buf, ".");

    dStringVector rand = initStringVector(2);
    intToStr(rand[0], randInt());
    intToStr(rand[1], randInt());

    if (count == 0) {
        concatStr(baseName, 3, "_", rand[0], rand[1]);
        return;
    }

    dStringVector bufVec = initStringVector(count);
    explode(buf, ".", bufVec);

    concatStr(baseName, 3, "_", rand[0], rand[1]);

    implode(bufVec, count, ".", buf);
    alterString(baseName, buf);

    freeStringVector(bufVec, count);
    freeString(buf);
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