#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <stdio.h>

#include "text_t_lib.h"

typedef enum {
    FORWARD  = 0,
    BACKWARD = 1,
    NO_SORT  = 2
} sort_mode_t;

void SkipNonAlphaSymbols(size_t* i, const string_t* str, sort_mode_t mode);
void SwapStrings(void* s1, void* s2, size_t width);

int CompareStringsForward(const void *str1, const void *str2);
int CompareStringsBackward(const void *str1, const void *str2);

#endif /* STRING_FUNCTIONS_H */

