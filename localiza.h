//
// Created by THALLES on 18/11/2019.
//

#ifndef LOCALIZA_LOCALIZA_H
#define LOCALIZA_LOCALIZA_H

#define FLAGS_COUNT 5

#define FLAG_HELP 0
#define FLAG_CASE 1
#define FLAG_COUNT 2
#define FLAG_NUMB 3
#define FLAG_OUT 4

typedef char *String;

typedef struct Option {
    int status;
    int (*verify)(String str);
} Option;

typedef struct Flags {
    int count;
    int active;
    Option *flags;
} Flags;

typedef struct Targets {
    int count;
    char **targets;
} Targets;

Option options[FLAGS_COUNT];
Flags flags;
Targets targets;

String sSearchTerm;

void help(String scriptname, int exitCode);

void checkFlagsExistence(int argc, char **argv, Option *flag);

int flagHelp(String str);

int flagCaseSensitive(String str);

int flagCount(String str);

int flagLineNumber(String str);

int flagOutput(String str);

size_t maxLength(int size, char **matrix);

void getFlagsFromArg(int argc, char **argv);

void getSearchTermFromArg(char **argv);

void getTargetsFromArg(int argc, char **argv);

void parseArguments(int argc, char **argv);

void garbageCollector();

void grep(String searchTerm);

int main(int argc, char **argv);

#endif //LOCALIZA_LOCALIZA_H
