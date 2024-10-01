#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <stdio.h>

#include "text_lib.h"
#include "define_constants.h"

void SkipNonAlphaSymbols(const string_t* str, size_t* i, sort_mode_t mode);

int CompareStringsForward(const void* str1, const void* str2);
int CompareStringsBackward(const void* str1, const void* str2);

#endif /* STRING_FUNCTIONS_H */

