#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <stdio.h>
#include "define_constants.h"

bool CompareStringsForward(size_t s1, size_t s2, string_t* text_strdata);
bool CompareStringsBackward(size_t s1, size_t s2, string_t* text_strdata);
void SwapStrings(size_t s1, size_t s2, string_t* text_strdata);

int CompareStringsForwardTest(const void *s1, const void *s2);

#endif /* STRING_FUNCTIONS_H */

