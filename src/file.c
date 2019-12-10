//
// Created by Thalles on 10/12/2019.
//

#include "file.h"
#include "targets.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * Function: scanDir
 * ----------------------------
 *   @brief crawl a directory for files and sub directories.
 *
 *   @category Grep
 *
 *   @param target  struct Targets witch contains targets information.
 *   @param path    path to the directory.
 */
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
    buf = concatStr(buf, 2, "/", dir->d_name);

    addTarget(target, buf);
    freeString(buf);
  }
  closedir(targetDir);
}

/**
 * Function: generateOutputFile
 * ----------------------------
 *   @brief Generate an output file.
 *
 *   @category Output File
 *
 *   @param name    name of the file to generate.
 *   @param content content to append to file.
 */
void generateOutputFile(dString name, dString content) {
  FILE *targetFile = fopen(name, "a");

  if (targetFile == NULL) {
    printf("%s: Unable to open file.\n", name);
    return;
  }

  fputs(content, targetFile);
  fclose(targetFile);
}

/**
 * Function: printMsgForFile
 * ----------------------------
 *   @brief print a message for a specific file.
 *
 *   @category File
 *
 *   @param target  struct Targets witch contains targets information.
 *   @param id      position of target in array.
 *   @param message message to display.
 */
void printMsgForFile(Targets target, unsigned int id, dString message) {
  printf("%s:%s\n", getTargetPath(target, id), message);
}

/**
 * Function: fileExists
 * ----------------------------
 *   @brief Verify if file exists.
 *
 *   @category File
 *
 *   @param path path to file.
 *
 *   @return 1 for true and 0 for false.
 */
int fileExists(dString path) {
  Stat statBuf;
  if (stat(path, &statBuf) == 0) {
    return 1;
  }
  return 0;
}

/**
 * Function: isFile
 * ----------------------------
 *   @brief verify if is file.
 *
 *   @category File
 *
 *   @param path path to file.
 *
 *   @return 1 for true and 0 for false.
 */
int isFile(dString path) {
  Stat statBuf;
  stat(path, &statBuf);

  if (stat(path, &statBuf) == 0) {
    return S_ISREG(statBuf.st_mode);
  }
  return 0;
}

/**
 * Function: isDir
 * ----------------------------
 *   @brief verify if is directory.
 *
 *   @category File
 *
 *   @param path path to file.
 *
 *   @return 1 for true and 0 for false.
 */
int isDir(dString path) {
  Stat statBuf;

  if (stat(path, &statBuf) == 0) {
    return S_ISDIR(statBuf.st_mode);
  }
  return 0;
}