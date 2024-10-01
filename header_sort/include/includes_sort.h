#ifndef INCLUDES_SORT_H
#define INCLUDES_SORT_H

#include <stdio.h>
#include <assert.h>

#include "define_constants.h"
#include "text_lib.h"

void SortIncludes(text_t* text);

int CompareIncludes(const void* str1, const void* str2);

#endif /* INCLUDES_SORT_H */
