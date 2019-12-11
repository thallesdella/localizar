//
// Created by Thalles on 21/11/2019.
//

#include "targets.h"
#include "file.h"
#include "flags.h"
#include "searchTerm.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Function: initTargets
 * ----------------------------
 *   @brief Initiate targets struct.
 *
 *   @category Target
 *
 *   @param target  struct Targets witch contains targets information.
 */
void initTargets(Targets *targets) {
  targets->count = 0;
  targets->totalHotLines = 0;
  targets->totalOccurrences = 0;
  targets->targets = malloc(sizeof(File));
}

/**
 * Function: addTarget
 * ----------------------------
 *   @brief Update de struct targets and add a new target to the struct.
 *
 *   @category Target
 *
 *   @param target      struct Targets witch contains targets information.
 *   @param targetPath  path to the file.
 */
void addTarget(Targets *targets, dString targetPath) {
  unsigned int id = targets->count;
  targets->count = targets->count + 1;
  targets->targets = realloc(targets->targets, sizeof(File) * targets->count);

  File *target = &targets->targets[id];
  target->occurrences = 0;
  target->hotLines = 0;
  target->isFile = isFile(targetPath);
  target->isDir = isDir(targetPath);
  target->path = initString(targetPath);
  target->ext = getFileExtension(targetPath);
  target->name = getFileName(targetPath);
  target->outputPath = (superGlobal.needOutputName && target->isFile
                            ? generateName(target->name, target->ext)
                            : NULL);

  if (superGlobal.isDebug == 1) {
    printf("[ADD_TARGET] %s - out:%s isFile:%d isDir:%d hotLines:%d "
           "occurrences:%d\n",
           target->path, target->outputPath, target->isFile, target->isDir,
           target->hotLines, target->occurrences);
  }
}

/**
 * Function: searchInTarget
 * ----------------------------
 *   @brief Search for a needle in a target file.
 *
 *   @category Grep
 *
 *   @param needle      struct SearchTerm witch contains count of needles
 *                      and needles.
 *   @param targetPath  path to the file.
 *   @param flags       struct Flags witch contains the flags and properties.
 *
 *   @returns:  array of int that indicates error status, hotLines
 *              and occurrences.
 */
int *searchInTarget(SearchTerm needle, File target, Flags flags) {
  FILE *targetFile = fopen(target.path, "r");
  int *r = malloc(sizeof(int) * 3);
  r[0] = 0;
  r[1] = 0;
  r[2] = 0;

  if (targetFile == NULL) {
    printf("%s:File not found", target.path);
    r[1] = 1;
    return r;
  }

  int line = 0;
  while (!feof(targetFile)) {
    line = line + 1;

    unsigned int maxSize = 128;
    dString buf = malloc(sizeof(char) * maxSize);

    char ch = (char)getc(targetFile);
    int count = 0;

    while ((ch != '\n') && (ch != EOF)) {
      if (count == maxSize) {
        maxSize += 128;
        buf = realloc(buf, sizeof(char) * maxSize);
      }

      buf[count] = ch;
      count = count + 1;
      ch = (char)getc(targetFile);
    }

    buf[count] = '\0';

    if ((count = countSearchTermOccurrence(needle, buf, flags)) > 0) {
      r[1] = r[1] + 1;
      r[2] = r[2] + count;

      if (getFlagStatus(flags, FLAG_COUNT) == 0) {
        if (getFlagStatus(flags, FLAG_NUMB)) {
          printf("%s:%d:%s\n", target.path, line, buf);
        } else {
          printf("%s:%s\n", target.path, buf);
        }
      }

      if (getFlagStatus(flags, FLAG_OUT)) {
        removeSearchTermFromString(buf, needle);
      }
    }

    if (getFlagStatus(flags, FLAG_OUT)) {
      buf = concatStr(buf, 1, "\n");
      generateOutputFile(target.outputPath, buf);
    }

    freeString(buf);
  }
  fclose(targetFile);
  return r;
}

/**
 * Function: getTargetPath
 * ----------------------------
 *   @brief Get the path for target's file.
 *
 *   @category Target
 *
 *   @param target  struct Targets witch contains targets information.
 *   @param id      position of target in array.
 *
 *   @return return the target's file path.
 */
dString getTargetPath(Targets target, unsigned int id) {
  return target.targets[id].path;
}