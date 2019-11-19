//
// Created by THALLES on 19/11/2019.
//

#ifndef LOCALIZA_FLAGS_H
#define LOCALIZA_FLAGS_H

#define FLAGS_COUNT 5

#define FLAG_HELP 0
#define FLAG_CASE 1
#define FLAG_COUNT 2
#define FLAG_NUMB 3
#define FLAG_OUT 4

typedef struct Option {
    int status;
    int (*verify)(String str);
} Option;

typedef struct Flags {
    int count;
    int active;
    Option *flags;
} Flags;

Option options[FLAGS_COUNT];
Flags flags;

void checkFlagsExistence(int argc, char **argv, Option *flag);

int flagHelp(String str);

int flagCaseSensitive(String str);

int flagCount(String str);

int flagLineNumber(String str);

int flagOutput(String str);

#endif //LOCALIZA_FLAGS_H
