//
// Created by THALLES on 18/11/2019.
//

#ifndef LOCALIZA_LOCALIZA_H
#define LOCALIZA_LOCALIZA_H

typedef char *String;

typedef struct Targets {
    int count;
    char **targets;
} Targets;

Targets targets;

String sSearchTerm;

void help(String scriptname, int exitCode);

void getFlagsFromArg(int argc, char **argv);

void getSearchTermFromArg(char **argv);

void getTargetsFromArg(int argc, char **argv);

void parseArguments(int argc, char **argv);

void grep(String searchTerm);

int main(int argc, char **argv);

#endif //LOCALIZA_LOCALIZA_H
