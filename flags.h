//
// Created by THALLES on 19/11/2019.
//

#ifndef LOCALIZA_FLAGS_H
#define LOCALIZA_FLAGS_H

#include "dstring.h"

#define FLAGS_COUNT 5

#define FLAG_HELP 0
#define FLAG_CASE 1
#define FLAG_COUNT 2
#define FLAG_NUMB 3
#define FLAG_OUT 4

typedef struct Option {
    int status;

    int (*verify)(dString str);
} Option;

typedef struct Flags {
    int count;
    int active;
    Option *flags;
} Flags;

Option options[FLAGS_COUNT];
Flags flags;

void checkFlagsExistence(int argc, dStringVector argv, Option *flag);

int getFlagStatus(int id);

int flagHelp(dString str);

int flagCaseSensitive(dString str);

int flagCount(dString str);

int flagLineNumber(dString str);

int flagOutput(dString str);

#endif //LOCALIZA_FLAGS_H
