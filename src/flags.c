//
// Created by THALLES on 19/11/2019.
//

#include "flags.h"
#include "dstring.h"
#include "helpers.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function: initString
 * ----------------------------
 *   @brief initiate flags struct.
 *
 *   @param flags       struct Flags witch will contains information of all
 *                      flags and others.
 *   @param option      struct Options witch contains a flag information.
 *   @param names       string vector containing flags names.
 *   @param func        array of pointers to verify function.
 *   @param flagsCount  count of flags.
 */
void initFlags(Flags *flags, Option *option, dStringVector names,
               VecFlagsFunc *func, int flagsCount) {
  for (int i = 0; i < flagsCount; ++i) {
    option[i].name = initString(names[i]);
    option[i].status = 0;
    option[i].verify = func[i];
  }

  flags->active = 0;
  flags->count = flagsCount;
  flags->flags = option;

  freeStringVector(names, flagsCount);
  free(func);
}

/**
 * Function: displayFlagHelp
 * ----------------------------
 *   @brief display help screen.
 *
 *   @param scriptName  name of the running script.
 *   @param exitCode    exit code number.
 */
void displayFlagHelp(dString scriptName, int exitCode) {
  printf("-- USAGE --\n");
  printf("\t./%s [OPTION]... PATTERN [FILE|DIRECTORY]...\n", scriptName);
  printf("\t./%s jesus bible.txt all-bibles-in-the-world\n\n", scriptName);
  printf("-- OPTIONS --\n");
  printf("\t-h --help\t - Display help\n");
  printf("\t-i --case\t - Case sensitive search disable\n");
  printf("\t-c --count\t - Display count of lines with has appearances of the "
         "pattern\n");
  // printf("\t-o --time\t - Display occurrences os the pattern in the file\n");
  printf("\t-n --numb\t - Display line number witch contains the pattern \n");
  printf("\t-d --out\t - Save an output copy without the pattern\n");

  exit(exitCode);
}

/**
 * Function: displayFlagCount
 * ----------------------------
 *   @brief display number of lines with had an occurrence of the SearchTerm.
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
 *   @brief verify if a certain flag exists in arguments passed.
 *
 *   @param flags   struct Flags witch contains information of all flags and
 *                  others.
 *   @param option  struct Options witch contains a flag information.
 *   @param argc    argc arguments count.
 *   @param argv    arguments array.
 */
void checkFlagsExistence(Flags *flags, unsigned int id, int argc,
                         dStringVector argv) {
  for (int i = 1; i < argc; ++i) {
    if (flags->flags[id].verify(argv[i])) {
      updateFlagStatus(flags, id, 1);
      return;
    }
  }
}

/**
 * Function: updateFlagStatus
 * ----------------------------
 *   @brief update flag status.
 *
 *   @param flags   pointer to struct Flags witch contains information of all
 *                  flags and others.
 *   @param id      position of flag in array.
 *   @param status  status of the flag.
 */
void updateFlagStatus(Flags *flags, unsigned int id, int status) {
  flags->flags[id].status = status;

  dString msg = malloc(sizeof(char) * (strlen(getFlagName(*flags, id)) + 21));
  if (status == 1) {
    flags->active = flags->active + 1;
    sprintf(msg, "[FLAGS] %s activated", getFlagName(*flags, id));
  } else {
    flags->active = flags->active - 1;
    sprintf(msg, "[FLAGS] %s deactivated", getFlagName(*flags, id));
  }
  printDebugMsg(msg);
  freeString(msg);
}

/**
 * Function: getFlagName
 * ----------------------------
 *   @brief return the name of the flag for the id given.
 *
 *   @param flags   struct Flags witch contains information of all flags and
 *                  others.
 *   @param id      position of flag in array.
 *
 *   @return name of the flag.
 */
dString getFlagName(Flags flags, unsigned int id) {
  return flags.flags[id].name;
}

/**
 * Function: getFlagStatus
 * ----------------------------
 *   @brief get the flag status.
 *
 *   @param flags   struct Flags witch contains information of all flags and
 *                  others.
 *   @param id      position of flag in array.
 *
 *   @return target's file path.
 */
int getFlagStatus(Flags flags, int id) { return flags.flags[id].status; }

/**
 * Function: flagDebug
 * ----------------------------
 *   @brief verification function for flag debug.
 *
 *   @param arg argument to be verified.
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
 *   @brief verification function for flag help.
 *
 *   @param arg argument to be verified.
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
 *   @brief verification function for flag case sensitive.
 *
 *   @param arg argument to be verified.
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
 *   @brief verification function for flag count lines that have occurrences.
 *
 *   @param arg argument to be verified.
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
 *   @brief verification function for flag occurrences.
 *
 *   @param arg argument to be verified.
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
 *   @brief verification function for flag display number of the line.
 *
 *   @param arg argument to be verified.
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
 *   @brief verification function for flag generate clean output file.
 *
 *   @param arg argument to be verified.
 *
 *   @return return 1 for true or 0 for false.
 */
int flagOutput(dString arg) {
  if (strcmp(arg, "-d") == 0 || strcmp(arg, "--out") == 0) {
    return 1;
  }
  return 0;
}