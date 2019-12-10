//
// Created by Thalles on 21/11/2019.
//

#include "searchTerm.h"
#include "dstring.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

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
