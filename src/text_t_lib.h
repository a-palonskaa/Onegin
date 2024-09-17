#ifndef TEXT_T_LIB_H
#define TEXT_T_LIB_H

#include <stdio.h>

#include "define_constants.h"

const size_t SORT_TYPES_CNT = 3;

typedef enum {
    NO_ERRORS               = 0,
    FILE_READ_ERROR         = 1,
    MEMORY_ALLOCATE_ERROR   = 2,
    INFILE_PTR_MOVING_ERROR = 3,
    EMPTY_FILE_ERROR        = 4
} error_t;

ssize_t CountTextSymbols(FILE* input_file);
ssize_t FindFileSize(FILE* input_file);
size_t CountTextLines(text_t* text);

void GetTextSymbols(text_t* text, FILE* input_file);
void ParseText(text_t* text);

error_t StringCtor(text_t* text, FILE* input_file);
void StringDtor(text_t* text);
void CopyStrings(string_t* src, string_t* dst, size_t str_cnt);
#endif /* TEXT_T_LIB_H */

