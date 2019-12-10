//
// Created by THALLES on 19/11/2019.
//

#include "flags.h"
#include "dstring.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function: initString
 * ----------------------------
 *   @brief Initiate flags struct.
 *
 *   @category Flags
 *
 *   @param flags       struct Flags witch will contains information of all
 *                      flags and others.
 *   @param option      struct Options witch contains a flag information.
 *   @param func        array of pointers to verify function.
 *   @param flagsCount  count of flags.
 */
void initFlags(Flags *flags, Option *option, VecFlagsFunc *func,
               int flagsCount) {
  for (int i = 0; i < flagsCount; ++i) {
    option[i].status = 0;
    option[i].verify = func[i];
  }

  flags->active = 0;
  flags->count = flagsCount;
  flags->flags = option;
}

/**
 * Function: displayFlagHelp
 * ----------------------------
 *   @brief Display help screen.
 *
 *   @category Help
 *
 *   @param scriptName  nme of the running script.
 *   @param exitCode    exit code number.
 */
void displayFlagHelp(dString scriptName, int exitCode) {
  printf("-- USAGE --\n");
  printf("\t./%s [null|flags...] [pattern] [file|dir...]\n", scriptName);
  printf("\t./%s jesus bible.txt all-bibles-in-the-world\n\n", scriptName);
  printf("-- FLAGS --\n");
  printf("\t-h --help\t - Display help\n");
  printf("\t-i --case\t - Case sensitive search disable\n");
  printf("\t-c --count\t - Display count of lines with has appearances of the "
         "pattern\n");
  // printf("\t-o --time\t - Display occurrences os the pattern in the file\n");
  printf("\t-n --numb\t - Display line number witch contains the pattern \n");
  // printf("\t-d --out\t - Save an output copy without the pattern\n");

  exit(exitCode);
}

/**
 * Function: displayFlagCount
 * ----------------------------
 *   @brief Display number of lines with had an occurrence of the SearchTerm.
 *
 *   @category Count Occurrences
 *
 *   @param target struct Targets witch contains targets information.
 */
void displayFlagCount(Targets target) {
  printf("OCCURRENCES: \n");

  for (unsigned int i = 0; i < target.count; ++i) {
    if (target.targets[i].isFile) {
      printf("\t%s:%u %s\n", target.targets[i].path, target.targets[i].hotLines,
             (target.targets[i].hotLines > 1 ? "founds" : "found"));
    }
  }

  if (target.count > 1) {
    printf("TOTAL:%u %s\n", target.totalHotLines,
           (target.totalHotLines > 1 ? "founds" : "found"));
  }
}

/**
 * Function: checkFlagsExistence
 * ----------------------------
 *   @brief Verify is a certain flag exists in arguments passed.
 *
 *   @category Flags
 *
 *   @param flags   struct Flags witch contains information of all flags and
 *                  others.
 *   @param option  struct Options witch contains a flag information.
 *   @param argc    argc arguments count.
 *   @param argv    arguments array.
 */
void checkFlagsExistence(Flags *flags, Option *option, int argc,
                         dStringVector argv) {
  for (int i = 1; i < argc; ++i) {
    if (option->verify(argv[i])) {
      option->status = 1;

      flags->active = flags->active + 1;

      if (superGlobal.isDebug == 1) {
        printf("[FLAGS] %s status:active\n", argv[i]);
      }
      return;
    }
  }
}

/**
 * Function: getFlagStatus
 * ----------------------------
 *   @brief Get the flag status.
 *
 *   @category Flags
 *
 *   @param flags   struct Flags witch contains information of all flags and
 *                  others.
 *   @param id      position of flag in array.
 *
 *   @return return the target's file path.
 */
int getFlagStatus(Flags flags, int id) { return flags.flags[id].status; }

/**
 * Function: flagDebug
 * ----------------------------
 *   @brief Verification function for flag debug.
 *
 *   @category Debug
 *
 *   @param arg argument to be verified
 *
 *   @return return 1 for true or 0 for false.
 */
int flagDebug(dString arg) {
  if (strcmp(arg, "--debug") == 0) {
    superGlobal.isDebug = 1;
    return 1;
  }
  return 0;
}

/**
 * Function: flagHelp
 * ----------------------------
 *   @brief Verification function for flag help.
 *
 *   @category Help
 *
 *   @param arg argument to be verified
 *
 *   @return return 1 for true or 0 for false.
 */
int flagHelp(dString arg) {
  if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
    return 1;
  }
  return 0;
}

/**
 * Function: flagCaseSensitive
 * ----------------------------
 *   @brief Verification function for flag case sensitive.
 *
 *   @category Case Sensitive
 *
 *   @param arg argument to be verified
 *
 *   @return return 1 for true or 0 for false.
 */
int flagCaseSensitive(dString arg) {
  if (strcmp(arg, "-i") == 0 || strcmp(arg, "--case") == 0) {
    return 1;
  }
  return 0;
}

/**
 * Function: flagCount
 * ----------------------------
 *   @brief Verification function for flag count lines that have occurrences.
 *
 *   @category Count Occurrences
 *
 *   @param arg argument to be verified
 *
 *   @return return 1 for true or 0 for false.
 */
int flagCount(dString arg) {
  if (strcmp(arg, "-c") == 0 || strcmp(arg, "--count") == 0) {
    return 1;
  }
  return 0;
}

/**
 * Function: flagOccurrences
 * ----------------------------
 *   @brief Verification function for flag occurrences.
 *
 *   @category Count Occurrences
 *
 *   @param arg argument to be verified
 *
 *   @return return 1 for true or 0 for false.
 */
int flagOccurrences(dString arg) {
  if (strcmp(arg, "-o") == 0 || strcmp(arg, "--time") == 0) {
    return 1;
  }
  return 0;
}

/**
 * Function: flagLineNumber
 * ----------------------------
 *   @brief Verification function for flag display number of the line.
 *
 *   @category Line Number
 *
 *   @param arg argument to be verified
 *
 *   @return return 1 for true or 0 for false.
 */
int flagLineNumber(dString arg) {
  if (strcmp(arg, "-n") == 0 || strcmp(arg, "--numb") == 0) {
    return 1;
  }
  return 0;
}

/**
 * Function: flagOutput
 * ----------------------------
 *   @brief Verification function for flag generate clean output file.
 *
 *   @category Output File
 *
 *   @param arg argument to be verified
 *
 *   @return return 1 for true or 0 for false.
 */
int flagOutput(dString arg) {
  if (strcmp(arg, "-d") == 0 || strcmp(arg, "--out") == 0) {
    return 1;
  }
  return 0;
}