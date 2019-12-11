//
// Created by Thalles on 10/12/2019.
//

#ifndef LOCALIZA_FILE_H
#define LOCALIZA_FILE_H

#include "helpers.h"

typedef struct stat Stat;

void scanDir(Targets *target, dString path);

void generateOutputFile(dString name, dString content);

void printMsgForFile(Targets target, unsigned int id, dString message);

dString getFileExtension(dString filename);

dString getFileName(dString filename);

int fileExists(dString path);

int isFile(dString path);

int isDir(dString path);

#endif // LOCALIZA_FILE_H
