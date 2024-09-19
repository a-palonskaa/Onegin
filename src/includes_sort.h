#ifndef INCLUDES_SORT_H
#define INCLUDES_SORT_H

#include <stdio.h>
#include "define_constants.h"

typedef struct {
    string_t string;
    char* include_name;
} include_strings_t;

void SortIncludes(text_t* text, FILE* output_file);

int CompareIncludes(const void* str1, const void* str2);

#endif /* INCLUDES_SORT_H */
