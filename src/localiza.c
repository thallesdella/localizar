//
// Created by THALLES on 18/11/2019.
//

#include "localiza.h"
#include "dstring.h"
#include "flags.h"
#include "helpers.h"
#include "searchTerm.h"
#include "structs.h"
#include "targets.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Function: getFlagsFromArg
 * ----------------------------
 *   @brief Loop through flags to see if they where enabled.
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
 *   @param argc arguments count.
 *   @param argv arguments array.
 */
void getTargetsFromArg(int argc, dStringVector argv) {
  unsigned int initTargetPosition = flags.active + 2;

  for (unsigned int i = initTargetPosition; i < argc; ++i) {
    addTarget(&targets, argv[i]);
  }
}

/**
 * Function: parseArguments
 * ----------------------------
 *   @brief responsible to call functions that handle arguments parse and
 *      construct theirs structs.
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
  for (int i = 0; i < searchTerm.count; ++i) {
    printf("parse - needle:%s\n", searchTerm.terms[i]);
  }
}

/**
 * Function: grep
 * ----------------------------
 *   @brief loop through targets to scan the directory, or to perform a search
 *      in a file.
 */
void grep(void) {
  for (int i = 0; i < searchTerm.count; ++i) {
    printf("grep - needle:%s\n", searchTerm.terms[i]);
  }

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

      int *result =
          searchInTarget(searchTerm, getTargetPath(targets, i), flags);
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
 * Function: garbageCollector
 * ----------------------------
 *   @brief Deallocate memory allocated during the execution of this script.
 */
void garbageCollector() {
  printDebugMsg("[MAIN] Cleaning the dirt");
  for (unsigned int i = 0; i < flags.count; ++i) {
    freeString(flags.flags[i].name);
  }
  free(options);

  freeStringVector(searchTerm.terms, searchTerm.count);

  for (unsigned int i = 0; i < targets.count; ++i) {
    free(getTargetPath(targets, i));
  }
  free(targets.targets);
}

/**
 * Function: main
 * ----------------------------
 *   @brief entry point of this script.
 *
 *   @param argc arguments count.
 *   @param argv arguments array.
 *
 *   @return
 */
int main(int argc, dStringVector argv) {
  superGlobal.isDebug = 0;

  VecFlagsFunc *verifyFlags = malloc(sizeof(VecFlagsFunc) * FLAGS_COUNT);
  dStringVector flagsName = initStringVector(FLAGS_COUNT);
  options = malloc(sizeof(Option) * FLAGS_COUNT);

  verifyFlags[FLAG_DEBUG] = flagDebug;
  verifyFlags[FLAG_HELP] = flagHelp;
  verifyFlags[FLAG_CASE] = flagCaseSensitive;
  verifyFlags[FLAG_NUMB] = flagLineNumber;
  verifyFlags[FLAG_COUNT] = flagCount;
  verifyFlags[FLAG_OCCUR] = flagOccurrences;
  verifyFlags[FLAG_OUT] = flagOutput;

  printf("teste\n");

  alterString(flagsName[FLAG_DEBUG], "Debug");
  alterString(flagsName[FLAG_HELP], "Help");
  alterString(flagsName[FLAG_CASE], "Case Sensitive");
  alterString(flagsName[FLAG_NUMB], "Show Line Number");
  alterString(flagsName[FLAG_COUNT], "Count Line");
  alterString(flagsName[FLAG_OCCUR], "Count Occurrences");
  alterString(flagsName[FLAG_OUT], "Generate Output");

  initFlags(&flags, options, flagsName, verifyFlags, FLAGS_COUNT);

  initSearchTerm(&searchTerm);
  initTargets(&targets);
  printDebugMsg("[MAIN] Finish Init");

  parseArguments(argc, argv);
  printDebugMsg("[MAIN] Finish argument parse");
  checkConflicts();

  grep();

  if (getFlagStatus(flags, FLAG_COUNT) == 1) {
    displayFlagCount(targets);
  }
  printDebugMsg("[MAIN] Finish grep");

  garbageCollector();
  return 0;
}
