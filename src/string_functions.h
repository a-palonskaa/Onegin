#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <stdio.h>
#include "define_constants.h"

bool CompareStrFirst(size_t s1, size_t s2, str_store_data_t* text_strdata);
bool CompareStrLast(size_t s1, size_t s2, str_store_data_t* text_strdata);
void SwapStr(size_t s1, size_t s2, str_store_data_t* text_strdata);

#endif /* STRING_FUNCTIONS_H */
