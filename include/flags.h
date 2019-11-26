//
// Created by THALLES on 19/11/2019.
//

#ifndef LOCALIZA_FLAGS_H
#define LOCALIZA_FLAGS_H

#include "structs.h"
#include "dstring.h"

#define FLAG_HELP 0
#define FLAG_CASE 1
#define FLAG_COUNT 2
#define FLAG_NUMB 3
#define FLAG_OUT 4

typedef int (*Vflags)(dString);

void initFlags(Flags *structFlags, Option *arrStructOption, Vflags *func, int flagsCount);

void displayFlagHelp(dString scriptName, int exitCode);

void displayFlagCount(Targets target);

void checkFlagsExistence(Flags *flags, Option *option, int argc, dStringVector argv);

int getFlagStatus(Flags flags, int id);

int flagHelp(dString str);

int flagCaseSensitive(dString str);

int flagCount(dString str);

int flagLineNumber(dString str);

int flagOutput(dString str);

#endif //LOCALIZA_FLAGS_H
