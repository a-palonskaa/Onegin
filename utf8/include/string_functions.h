#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <stdio.h>

#include "utf8_text.h"
#include "defines.h"
#include "parse_arguments.h"

void SkipNonAlphaSymbols(const string_t* str, size_t* i, sort_mode_t mode);

bool IsAlphaUtf8(uint32_t code);
uint32_t ToLowerUTF8(uint32_t code);

int CompareStringsForward(const void* str1, const void* str2);
int CompareStringsBackward(const void* str1, const void* str2);

#endif /* STRING_FUNCTIONS_H */

