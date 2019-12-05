//
// Created by THALLES on 19/11/2019.
//

#ifndef LOCALIZA_FLAGS_H
#define LOCALIZA_FLAGS_H

#include "dstring.h"
#include "structs.h"

//#define FLAG_DEBUG 0
#define FLAG_HELP 1
#define FLAG_CASE 2
#define FLAG_COUNT 3
#define FLAG_NUMB 4
#define FLAG_OUT 5

typedef int (*VecFlagsFunc)(dString);

void initFlags(Flags *structFlags, Option *arrStructOption, VecFlagsFunc *func,
               int flagsCount);

void displayFlagHelp(dString scriptName, int exitCode);

void displayFlagCount(Targets target);

void checkFlagsExistence(Flags *flags, Option *option, int argc,
                         dStringVector argv);

int getFlagStatus(Flags flags, int id);

int flagDebug(dString str);

int flagHelp(dString str);

int flagCaseSensitive(dString str);

int flagCount(dString str);

int flagLineNumber(dString str);

int flagOutput(dString str);

#endif // LOCALIZA_FLAGS_H
