//
// Created by Thalles on 21/11/2019.
//

#include "searchTerm.h"
#include "flags.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function: initSearchTerm
 * ----------------------------
 *   @brief Initiate SearchTerm struct.
 *
 *   @category Search Term
 *
 *   @param searchTerm pointer struct SearchTerm witch contains count of needles
 *                     and needles.
 */
void initSearchTerm(SearchTerm *searchTerm) {
  searchTerm->count = 0;
  searchTerm->terms = initStringVector(searchTerm->count);
}

/**
 * Function: addSearchTerm
 * ----------------------------
 *   @brief Update de struct SearchTerm and add a new term to the struct.
 *
 *   @category Search Term
 *
 *   @param searchTerm  pointer struct SearchTerm witch contains count of
 *                      needles and needles it self.
 *   @param term        term to be add to the SearchTerm struct.
 */
void addSearchTerm(SearchTerm *searchTerm, dString term) {
  searchTerm->count = countAppearances(term, "*") + 1;
  searchTerm->terms =
      realloc(searchTerm->terms, sizeof(dString) * searchTerm->count);
  /*int newSize = countAppearances(term, "*") + 1;
  searchTerm->terms =
      changeStringVectorSize(searchTerm->terms, searchTerm->count, newSize);
  searchTerm->count = newSize;*/

  if (searchTerm->count > 1) {
    explode(term, "*", searchTerm->terms);
  } else {
    searchTerm->terms[0] = initString(term);
    // alterString(searchTerm->terms[0], term);
  }

  if (superGlobal.isDebug == 1) {
    for (int i = 0; i < searchTerm->count; ++i) {
      printf("[ADD_SEARCH_TERM] %s\n", searchTerm->terms[i]);
    }
  }
}

/**
 * Function: removeSearchTermFromLine
 * ----------------------------
 *   @brief remove the terms from a string.
 *
 *   @category Output File
 *
 *   @param string      line to be altered.
 *   @param searchTerm  struct SearchTerm witch contains count of needles
 *                      and needles.
 */
void removeSearchTermFromString(dString string, SearchTerm searchTerm) {
  for (int i = 0; i < searchTerm.count; ++i) {
    removeSubstr(string, searchTerm.terms[i]);
  }
}

/**
 * Function: countSearchTermOccurrence
 * ----------------------------
 *   @brief loop through an array of needles to count their occurrences in a
 *      sentence.
 *
 *   @category Count Occurrences
 *
 *   @param needle      struct SearchTerm witch contains count of needles
 *                      and needles.
 *   @param haystack    sentence to be verified.
 *   @param flags       struct Flags witch contains the flags and properties.
 *
 *   @return will return the count of occurrences.
 */
int countSearchTermOccurrence(SearchTerm needle, dString haystack,
                              Flags flags) {
  int count = 0;
  dString buf = initString(haystack);

  while (verifySearchTermPresence(needle, buf, flags)) {
    count = count + 1;
  }

  freeString(buf);
  return count;
}

/**
 * Function: verifySearchTermPresence
 * ----------------------------
 *   @brief loop through an array of needles to verify their presence in a
 *      sentence.
 *
 *   @category Grep
 *
 *   @param needle      struct SearchTerm witch contains count of needles
 *                      and needles.
 *   @param haystack    sentence to be verified.
 *   @param flags       struct Flags witch contains the flags and properties.
 *
 *   @return return 1 if the needles are present otherwise 0.
 */
int verifySearchTermPresence(SearchTerm needle, dString haystack, Flags flags) {
  int testsPassed = 0;

  for (unsigned int i = 0; i < needle.count; ++i) {
    dString hasString =
        (!getFlagStatus(flags, FLAG_CASE)
             ? strstr(strToLower(haystack), strToLower(needle.terms[i]))
             : strstr(haystack, needle.terms[i]));

    if (hasString != NULL) {
      testsPassed = testsPassed + 1;
      memcpy(haystack, hasString + 1, strlen(hasString) + 1);
    }
  }

  return testsPassed == needle.count;
}