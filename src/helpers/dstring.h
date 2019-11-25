//
// Created by Thalles on 19/11/2019.
//

#ifndef LOCALIZA_DSTRING_H
#define LOCALIZA_DSTRING_H

typedef char *dString;
typedef char **dStringVector;

dString initString(dString content);

void alterString(dString string, dString content);

void freeString(dString string);

dStringVector initStringVector(unsigned int size);

void copyStringVector(dStringVector vector, unsigned int size, dStringVector content);

void freeStringVector(dStringVector string, unsigned int size);

dString strToLower(dString string);

dString strToUpper(dString string);

void applyFuncToStrings(dStringVector vector, unsigned int size, dString (*func)(dString));

int countAppearances(dString string, dString token);

void explode(dString string, dString delimiter, dStringVector result);

void implode(dStringVector vector, unsigned int size, dString glue, dString result);

#endif //LOCALIZA_DSTRING_H
