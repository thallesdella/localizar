//
// Created by THALLES on 19/11/2019.
//

#ifndef LOCALIZA_FLAGS_H
#define LOCALIZA_FLAGS_H

#include "helpers.h"

//#define FLAG_DEBUG 0
#define FLAG_HELP 1
#define FLAG_CASE 2
#define FLAG_COUNT 3
#define FLAG_OCCUR 4
#define FLAG_NUMB 5
#define FLAG_OUT 6

typedef int (*VecFlagsFunc)(dString);

void initFlags(Flags *flags, Option *option, dStringVector name,
               VecFlagsFunc *func, int flagsCount);

void displayFlagHelp(dString scriptName, int exitCode);

void displayFlagHotLines(Targets target);

void displayFlagOccurrences(Targets target);

void checkFlagsExistence(Flags *flags, unsigned int id, int argc,
                         dStringVector argv);

void updateFlagStatus(Flags *flags, unsigned int id, int status);

dString getFlagName(Flags flags, unsigned int id);

int getFlagStatus(Flags flags, int id);

int flagDebug(dString arg);

int flagHelp(dString arg);

int flagCaseSensitive(dString arg);

int flagHotLines(dString arg);

int flagOccurrences(dString arg);

int flagLineNumber(dString arg);

int flagOutput(dString arg);

#endif // LOCALIZA_FLAGS_H
