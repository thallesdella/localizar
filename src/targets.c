//
// Created by Thalles on 21/11/2019.
//

#include "targets.h"
#include "dstring.h"
#include "flags.h"
#include "helpers.h"
#include "searchTerm.h"
#include "structs.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function: searchInTarget
 * ----------------------------
 *   @brief Search for a needle in a target file.
 *
 *   @param needle      struct SearchTerm witch contains count of needles
 *                      and needles.
 *   @param targetPath  path to the file.
 *   @param flags       struct Flags witch contains the flags and properties.
 *
 *   @returns:  array of int that indicates error status, hotLines
 *              and occurrences.
 */
int *searchInTarget(SearchTerm needle, dString targetPath, Flags flags) {
  for (int i = 0; i < needle.count; ++i) {
    printf("target - needle:%s\n", needle.terms[i]);
  }

  FILE *targetFile = fopen(targetPath, "r");
  int *r = malloc(sizeof(int) * 3);
  r[0] = 0;
  r[1] = 0;
  r[2] = 0;

  if (targetFile == NULL) {
    printf("%s:File not found", targetPath);
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
          printf("%s:%d:%s\n", targetPath, line, buf);
        } else {
          printf("%s:%s\n", targetPath, buf);
        }
      }

      if (getFlagStatus(flags, FLAG_OUT)) {
        dString cleanStr = initString(buf);
        removeSearchTermFromString(cleanStr, needle);
        generateOutputFile(targetPath, cleanStr);
      }
    }
    freeString(buf);
  }
  fclose(targetFile);
  return r;
}

/**
 * Function: scanDir
 * ----------------------------
 *   @brief Search crawl a directory for files and directories.
 *
 *   @param target  struct Targets witch contains targets information.
 *   @param path    path to the directory.
 */
void scanDir(Targets *target, dString path) {
  printDebugMsg("[SCAN_DIRECTORY] scanning dir...");
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
    concatStr(&buf, 2, "/", dir->d_name);

    addTarget(target, buf);
    freeString(buf);
  }
  closedir(targetDir);
}

/**
 * Function: initTargets
 * ----------------------------
 *   @brief Initiate targets struct.
 *
 *   @param target  struct Targets witch contains targets information.
 */
void initTargets(Targets *targets) {
  targets->count = 0;
  targets->totalHotLines = 0;
  targets->totalOccurrences = 0;
  targets->targets = malloc(sizeof(Target));
}

/**
 * Function: addTarget
 * ----------------------------
 *   @brief Update de struct targets and add a new target to the struct.
 *
 *   @param target      struct Targets witch contains targets information.
 *   @param targetPath  path to the file.
 */
void addTarget(Targets *targets, dString targetPath) {
  unsigned int id = targets->count;

  targets->count = targets->count + 1;

  if (targets->count > 1) {
    targets->targets =
        realloc(targets->targets, sizeof(Target) * targets->count);
  }

  Target *target = &targets->targets[id];
  target->occurrences = 0;
  target->hotLines = 0;
  target->isFile = isFile(targetPath);
  target->isDir = isDir(targetPath);
  target->path = initString(targetPath);

  if (superGlobal.isDebug == 1) {
    printf("[ADD_TARGET] %s - isFile:%d isDir:%d hotLines:%d occurrences:%d\n",
           target->path, target->isFile, target->isDir, target->hotLines,
           target->occurrences);
  }
}

/**
 * Function: generateOutputFile
 * ----------------------------
 *   @brief Generate an output file.
 *
 *   @param name    name of the file to generate.
 *   @param content content to append to file.
 */
void generateOutputFile(dString name, dString content) {
  dString buf = initString(name);
  printf("before:%s\n", buf);
  generateName(buf);
  printf("after:%s\n", buf);

  FILE *targetFile = fopen(buf, "a");

  if (targetFile == NULL) {
    printf("%s: Unable to open file.\n", buf);
    return;
  }

  fputs(content, targetFile);
  fclose(targetFile);
}

/**
 * Function: generateName
 * ----------------------------
 *   @brief Generate a new name adding random number to the end of the
 *      files's name.
 *
 *   @param baseName name to be altered.
 */
void generateName(dString baseName) {
  dString buf = initString(baseName);
  int count = countAppearances(buf, ".");

  dStringVector rand = initStringVector(2);
  intToStr(rand[0], randInt(9999, 1000));
  intToStr(rand[1], randInt(9999, 1000));

  if (count == 0) {
    // baseName = realloc(baseName, sizeof(char) * (strlen(baseName) + 10));
    // sprintf(baseName, "%s_%s%s", baseName, rand[0], rand[0]);
    concatStr(&baseName, 3, "_", rand[0], rand[1]);
    return;
  }

  dStringVector bufVec = initStringVector(count);
  explode(buf, ".", bufVec);

  int lastNamePiece = count - 1;
  /*bufVec[lastNamePiece] =
      realloc(bufVec[lastNamePiece],
              sizeof(char) * (strlen(bufVec[lastNamePiece]) + 10));
  sprintf(bufVec[lastNamePiece], "%s_%s%s", bufVec[lastNamePiece], rand[0],
          rand[1]);*/

  concatStr(&bufVec[lastNamePiece], 3, "_", rand[0], rand[1]);

  implode(bufVec, count, ".", buf);

  // printf("debug:%s\n", buf);
  baseName = realloc(baseName, sizeof(char) * (strlen(buf) + 1));
  strcpy(baseName, buf);
  // alterString(baseName, buf);
  // printf("basename:%s\n", baseName);

  freeStringVector(bufVec, count);
  freeString(buf);
}

/**
 * Function: printMsgForFile
 * ----------------------------
 *   @brief print a message for a specific file.
 *
 *   @param target  struct Targets witch contains targets information.
 *   @param id      position of target in array.
 *   @param message message to display.
 */
void printMsgForFile(Targets target, unsigned int id, dString message) {
  printf("%s:%s\n", getTargetPath(target, id), message);
}

/**
 * Function: getTargetPath
 * ----------------------------
 *   @brief Get the path for target's file.
 *
 *   @param target  struct Targets witch contains targets information.
 *   @param id      position of target in array.
 *
 *   @return return the target's file path.
 */
dString getTargetPath(Targets target, unsigned int id) {
  return target.targets[id].path;
}

/**
 * Function: readLine *BUG
 * ----------------------------
 *   @brief read line from a file.
 *
 *   @param file file pointer.
 *   @param line space in memory for saving the line content.
 *
 *   @return return the target's file path.
 */
void readLine(FILE *file, dString line) {
  if (file == NULL) {
    printf("Error: file pointer is null.");
    return;
  }

  unsigned int maxSize = 128;
  dString buf = malloc(sizeof(char) * maxSize);

  char ch = (char)getc(file);
  int count = 0;

  while ((ch != '\n') && (ch != EOF)) {
    if (count == maxSize) {
      maxSize += 128;
      buf = realloc(buf, sizeof(char) * maxSize);
    }

    buf[count] = ch;
    count = count + 1;
    ch = (char)getc(file);
  }

  buf[count] = '\0';
  alterString(line, buf);
  free(buf);
}

/**
 * Function: countSearchTermOccurrence
 * ----------------------------
 *   @brief loop through an array of needles to count their occurrences in a
 *      sentence.
 *
 *   @param needle      struct SearchTerm witch contains count of needles
 *                      and needles.
 *   @param haystack    sentence to be verified.
 *   @param flags       struct Flags witch contains the flags and properties.
 *
 *   @return will return the count of occurrences.
 */
int countSearchTermOccurrence(SearchTerm needle, dString haystack,
                              Flags flags) {
  int count = 0;
  dString buf = initString(haystack);

  while (verifySearchTermPresence(needle, buf, flags)) {
    count = count + 1;
    printf("occurrences:%d\n", count);
  }

  freeString(buf);
  return count;
}

/**
 * Function: verifySearchTermPresence
 * ----------------------------
 *   @brief loop through an array of needles to verify their presence in a
 *      sentence.
 *
 *   @param needle      struct SearchTerm witch contains count of needles
 *                      and needles.
 *   @param haystack    sentence to be verified.
 *   @param flags       struct Flags witch contains the flags and properties.
 *
 *   @return return 1 if the needles are present otherwise 0.
 */
int verifySearchTermPresence(SearchTerm needle, dString haystack, Flags flags) {
  int testsPassed = 0;

  for (unsigned int i = 0; i < needle.count; ++i) {
    dString hasString =
        (!getFlagStatus(flags, FLAG_CASE)
             ? strstr(strToLower(haystack), strToLower(needle.terms[i]))
             : strstr(haystack, needle.terms[i]));

    printf("needle:%s haystack:%s\n", needle.terms[i], haystack);
    if (hasString != NULL) {
      testsPassed = testsPassed + 1;
      strcpy(haystack, hasString + 1);
    }
  }

  return testsPassed == needle.count;
}