//
// Created by Thalles on 19/11/2019.
//

#ifndef LOCALIZA_DSTRING_H
#define LOCALIZA_DSTRING_H

typedef char *dString;
typedef char **dStringVector;

dString strToLower(dString string);

dString strToUpper(dString string);

int countAppearances(dString string, dString token);

void explode(dString string, dString delimiter, dStringVector result);

#endif //LOCALIZA_DSTRING_H
