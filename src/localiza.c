//
// Created by THALLES on 18/11/2019.
//

#include "localiza.h"
#include "file.h"
#include "flags.h"
#include "searchTerm.h"
#include "targets.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Function: getFlagsFromArg
 * ----------------------------
 *   @brief Loop through flags to see if they where enabled.
 *
 *   @category params
 *
 *   @param argc arguments count.
 *   @param argv arguments array.
 */
void getFlagsFromArg(int argc, dStringVector argv) {
  for (unsigned int i = 0; i < flags.count; ++i) {
    checkFlagsExistence(&flags, i, argc, argv);
  }
}

/**
 * Function: getSearchTermFromArg
 * ----------------------------
 *   @brief Retrieve from arguments the search term and pass to addTermSearch.
 *
 *   @category params
 *
 *   @param argv arguments array.
 */
void getSearchTermFromArg(dStringVector argv) {
  unsigned int searchTermPosition = flags.active + 1;
  addSearchTerm(&searchTerm, argv[searchTermPosition]);
}

/**
 * Function: getTargetsFromArg
 * ----------------------------
 *   @brief Obtain targets from arguments em pass to addTarget.
 *
 *   @category params
 *
 *   @param argc arguments count.
 *   @param argv arguments array.
 */
void getTargetsFromArg(int argc, dStringVector argv) {
  unsigned int initTargetPosition = flags.active + 2;
  unsigned int currentTargetPosition = initTargetPosition;
  unsigned int targetsCount = argc - initTargetPosition;

  for (unsigned int i = 0; i < targetsCount; ++i) {
    addTarget(&targets, argv[currentTargetPosition]);
    currentTargetPosition = currentTargetPosition + 1;
  }
}

/**
 * Function: parseArguments
 * ----------------------------
 *   @brief responsible to call functions that handle arguments parse and
 *      construct theirs structs.
 *
 *   @category params
 *
 *   @param argc arguments count.
 *   @param argv arguments array.
 */
void parseArguments(int argc, dStringVector argv) {
  getFlagsFromArg(argc, argv);

  if (getFlagStatus(flags, FLAG_HELP)) {
    displayFlagHelp(argv[0], EXIT_SUCCESS);
  }

  if (argc < 3) {
    displayFlagHelp(argv[0], EXIT_FAILURE);
  }

  getSearchTermFromArg(argv);
  getTargetsFromArg(argc, argv);
  printDebugMsg("[MAIN] Finish parsing arguments.");
}

/**
 * Function: checkConflicts
 * ----------------------------
 *   @brief Check to see if there is any conflicts between flags.
 */
void checkConflicts() {
  printDebugMsg("[MAIN] Checking conflicts");
  if (getFlagStatus(flags, FLAG_OUT) && searchTerm.count > 1) {
    updateFlagStatus(&flags, FLAG_OUT, 0);
    printf(
        "Warning: Generating an Output file only works with common search.\n");
  }
}

/**
 * Function: grep
 * ----------------------------
 *   @brief loop through targets to perform a scan to a directory, or a search
 *      in a file.
 *
 *   @category Grep
 */
void grep(void) {
  printDebugMsg("[MAIN] Start grep...");
  for (unsigned int i = 0; i < targets.count; ++i) {
    if (targets.targets[i].isDir) {
      scanDir(&targets, getTargetPath(targets, i));
    } else if (targets.targets[i].isFile) {
      if (getFlagStatus(flags, FLAG_COUNT) == 0) {
        if (i != 0) {
          printf("\n");
        }

        dString pathCopy = initString(getTargetPath(targets, i));
        printf("-- %s:\n", strToUpper(pathCopy));
        freeString(pathCopy);
      }

      int *result = searchInTarget(searchTerm, targets.targets[i], flags);
      if (result[0] == 0) {
        if (result[1] == 0) {
          printMsgForFile(targets, i, "Didnt find any occurrences");
        }

        targets.targets[i].hotLines = result[1];
        targets.targets[i].occurrences = result[2];
        targets.totalHotLines = targets.totalHotLines + result[1];
        targets.totalOccurrences = targets.totalOccurrences + result[2];
      }
      free(result);
    } else {
      if (!getFlagStatus(flags, FLAG_COUNT)) {
        printMsgForFile(targets, i, "File or directory dont exist");
      }
    }
  }

  if (getFlagStatus(flags, FLAG_COUNT) == 1) {
    displayFlagHotLines(targets);
  }

  if (getFlagStatus(flags, FLAG_OCCUR) == 1) {
    displayFlagOccurrences(targets);
  }
  printDebugMsg("[MAIN] Finish grep.");
}

/**
 * Function: garbageCollector
 * ----------------------------
 *   @brief Deallocate memory allocated during the execution of this script.
 *
 *   @category auxiliary
 */
void garbageCollector() {
  printDebugMsg("[MAIN] Cleaning the dirt...");
  free(options);

  freeStringVector(searchTerm.terms, searchTerm.count);

  for (unsigned int i = 0; i < targets.count; ++i) {
    freeString(getTargetPath(targets, i));
    freeString(targets.targets[i].outputPath);
  }
  free(targets.targets);
  printDebugMsg("[MAIN] Finish cleaning the dirt.");
}

/**
 * Function: main
 * ----------------------------
 *   @brief entry point of this script.
 *
 *   @category Main
 *
 *   @param argc arguments count.
 *   @param argv arguments array.
 *
 *   @return
 */
int main(int argc, dStringVector argv) {
  superGlobal.isDebug = 0;
  superGlobal.needOutputName = 0;

  options = malloc(sizeof(Option) * FLAGS_COUNT);
  VecFlagsFunc verifyFlags[FLAGS_COUNT] = {
      flagDebug,       flagHelp,       flagCaseSensitive, flagHotLines,
      flagOccurrences, flagLineNumber, flagOutput};

  dString names[FLAGS_COUNT] = {"Debug",
                                "Help",
                                "Case Sensitive",
                                "Count Hot Lines",
                                "Count Occurrences",
                                "Show Line Number",
                                "Generate Output"};

  initFlags(&flags, options, names, verifyFlags, FLAGS_COUNT);
  initSearchTerm(&searchTerm);
  initTargets(&targets);

  parseArguments(argc, argv);
  checkConflicts();

  grep();

  garbageCollector();
  return 0;
}
