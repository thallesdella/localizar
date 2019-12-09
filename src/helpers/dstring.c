//
// Created by Thalles on 19/11/2019.
//

#include "dstring.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function: initString
 * ----------------------------
 *   @brief Initiate string.
 *
 *   @param content content to attribute to string.
 *
 *   @return return pointer to string.
 */
dString initString(dString content) {
  if (content == NULL) {
    dString buf = calloc(1, sizeof(char));
    return buf;
  }

  size_t len = strlen(content) + 1;
  dString buf = malloc(sizeof(char) * len);
  strcpy(buf, content);
  return buf;
}

/**
 * Function: alterString
 * ----------------------------
 *   @brief alter string content.
 *
 *   @param string  target string.
 *   @param content content to attribute to string.
 */
void alterString(dString string, dString content) {
  size_t oldLen = strlen(string) + 1, newLen = strlen(content) + 1;

  if ((newLen + 16) < oldLen || newLen > oldLen) {
    string = realloc(string, sizeof(char) * newLen);
  }
  strcpy(string, content);
}

/**
 * Function: concatStr *BUG
 * ----------------------------
 *   @brief concatenate numb strings to a string.
 *
 *   @param string  target string.
 *   @param numb    number of strings to concatenate.
 *   @param ...     strings to concatenate.
 */
void concatStr(dString *string, int numb, ...) {
  va_list argsLen, args;
  size_t strLen = strlen(*string) + 1, newSize = strLen;

  va_start(args, numb);
  va_copy(argsLen, args);
  for (int i = 0; i < numb; ++i) {
    newSize = newSize + strlen(va_arg(argsLen, dString));
  }

  *string = realloc(*string, sizeof(char) * newSize);

  for (int i = 0; i < numb; ++i) {
    strcat(*string, va_arg(args, dString));
  }

  va_end(args);
}

/**
 * Function: freeString
 * ----------------------------
 *   @brief dealloc string.
 *
 *   @param string pointer to string.
 */
void freeString(dString string) { free(string); }

/**
 * Function: initStringVector
 * ----------------------------
 *   @brief initiate vector of strings.
 *
 *   @param size size of vector.
 *
 *   @return return a pointer to a vector of strings.
 */
dStringVector initStringVector(unsigned int size) {
  dStringVector buf = malloc(sizeof(dString) * size);

  for (unsigned int i = 0; i < size; ++i) {
    buf[i] = initString(NULL);
  }

  return buf;
}

/**
 * Function: copyStringVector
 * ----------------------------
 *   @brief copy a vector of strings to another.
 *
 *   @param vector  target vector of strings.
 *   @param size    size of vector.
 *   @param content content to be copied.
 */
void copyStringVector(dStringVector vector, unsigned int size,
                      dStringVector content) {
  for (unsigned int i = 0; i < size; ++i) {
    alterString(vector[i], content[i]);
  }
}

/**
 * Function: freeStringVector
 * ----------------------------
 *   @brief Deallocate vector of strings.
 *
 *   @param vector  target vector of strings.
 *   @param size    size of vector.
 */
void freeStringVector(dStringVector vector, unsigned int size) {
  for (unsigned int i = 0; i < size; ++i) {
    free(vector[i]);
  }
  free(vector);
}

/**
 * Function: strToLower
 * ----------------------------
 *   @brief transform string to lower case.
 *
 *   @param string target string.
 *
 *   @return return pointer to string.
 */
dString strToLower(dString string) {
  for (size_t i = 0; i < strlen(string); ++i) {
    string[i] = (char)tolower((int)string[i]);
  }
  return string;
}

/**
 * Function: strToUpper
 * ----------------------------
 *   @brief transform string to upper case.
 *
 *   @param string target string.
 *
 *   @return return pointer to string.
 */
dString strToUpper(dString string) {
  for (size_t i = 0; i < strlen(string); ++i) {
    string[i] = (char)toupper((int)string[i]);
  }
  return string;
}

/**
 * Function: applyFuncToStrings
 * ----------------------------
 *   @brief apply a function to each member of a vector
 *
 *   @param vector  target vector of strings.
 *   @param size    size of vector.
 *   @param func    function to be applied.
 */
void applyFuncToStrings(dStringVector vector, unsigned int size,
                        dString (*func)(dString)) {
  for (unsigned int i = 0; i < size; ++i) {
    vector[i] = func(vector[i]);
  }
}

/**
 * Function: removeSubstr
 * ----------------------------
 *   @brief remove sub string from an string.
 *
 *   @param string target string.
 *   @param remove position of target in array.
 */
void removeSubstr(dString string, dString remove) {
  size_t length = strlen(remove);
  while ((string = strstr(string, remove))) {
    memmove(string, string + length, 1 + strlen(string + length));
  }
}

/**
 * Function: intToStr
 * ----------------------------
 *   @brief Convert an int to a string.
 *
 *   @param string  target string.
 *   @param numb    int to be converted.
 */
void intToStr(dString string, unsigned int numb) {
  dString buf = malloc(sizeof(int) * 8 + 1);
  sprintf(buf, "%d", numb);

  size_t bufLen = strlen(buf) + 1;
  string = realloc(string, bufLen);

  memcpy(string, buf, bufLen);
  freeString(buf);
}

/**
 * Function: countAppearances
 * ----------------------------
 *   @brief Count the occurrences of a sub string in a string.
 *
 *   @param string  target string.
 *   @param token   sub string to be verified.
 *
 *   @return number of appearances in the string
 */
int countAppearances(dString string, dString token) {
  unsigned int sizeOfToken = strlen(token);
  dString positionOfToken = string;
  int i = 0;

  for (i; (positionOfToken = strstr(positionOfToken, token)) != NULL; ++i) {
    positionOfToken = positionOfToken + sizeOfToken;
  }

  return i;
}

/**
 * Function: explode
 * ----------------------------
 *   @brief divide a string into a vector by a delimiter.
 *
 *   @param string      target string.
 *   @param delimiter   position of target in array.
 *   @param result      buffer for vector of strings.
 */
void explode(dString string, dString delimiter, dStringVector result) {
  dString tok = strtok(string, delimiter);
  int i = 0, count = countAppearances(string, delimiter);

  result = realloc(result, sizeof(dString) * (count + 1));

  for (i; tok != NULL; ++i) {
    alterString(result[i], tok);
    tok = strtok(NULL, delimiter);
  }
}

/**
 * Function: implode
 * ----------------------------
 *   @brief put together an vector using a sub string.
 *
 *   @param vector  target vector of strings.
 *   @param size    size of vector.
 *   @param glue    string to go between the pieces.
 *   @param result  buffer for string.
 */
void implode(dStringVector vector, unsigned int size, dString glue,
             dString result) {
  size_t newLen = 0, glueLen = strlen(glue);

  for (unsigned int i = 0; i <= size; ++i) {
    newLen = newLen + strlen(vector[i]);
    if ((i + 1) < size) {
      newLen = newLen + glueLen;
    } else {
      newLen = newLen + 1;
    }
  }

  result = realloc(result, sizeof(char) * newLen);

  for (unsigned int i = 0; i <= size; ++i) {

    if (i == 0) {
      strcpy(result, vector[0]);
      strcat(result, glue);
      continue;
    }

    strcat(result, vector[i]);

    if ((i + 1) < size) {
      strcat(result, glue);
    }
  }
}
