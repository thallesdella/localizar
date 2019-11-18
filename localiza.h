//
// Created by THALLES on 18/11/2019.
//

#ifndef LOCALIZA_LOCALIZA_H
#define LOCALIZA_LOCALIZA_H

typedef struct Flags {
    int active;
    int help;
    int sensitive;
    int count;
    int line;
    int out;
} Flags;

Flags flags;

char *sSearchTerm;
char **aTargets;

void help(const char *scriptname);

int checkFlagsExistence(int argc, char **argv, const char *sFlags);

int flagHelp(int argc, char **argv);

int flagCaseSensitive(int argc, char **argv);

int flagCount(int argc, char **argv);

int flagLineNumber(int argc, char **argv);

int flagOutput(int argc, char **argv);

void getSearchTermFromArg(char **argv);

void getFlagsFromArg(int argc, char **argv);

#endif //LOCALIZA_LOCALIZA_H
