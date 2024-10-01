#ifndef TEXT_LIB_H
#define TEXT_LIB_H

#include <stdio.h>

#include "define_constants.h"
#include "parse_arguments.h"

typedef struct {
    char* begin;
    size_t length;
} string_t;

typedef struct {
    size_t symbols_amount;
    size_t strings_amount;

    char* symbols;

    sort_state_t sort_state;
    union {
        string_t* non_sorted;
        string_t** sorted;
    } strings;
} text_t;

const size_t SORT_TYPES_CNT = 3;

typedef enum {
    NO_ERRORS                     = 0,
    FILE_READ_ERROR               = 1,
    MEMORY_ALLOCATE_ERROR         = 2,
    INFILE_PTR_MOVING_ERROR       = 3,
    EMPTY_FILE_ERROR              = 4,
    PTR_POSITION_INDICATION_ERROR = 5,
} error_t;

ssize_t CountLeftTextSymbols(FILE* input_file);
ssize_t FindFileSize(FILE* input_file);
size_t CountTextLines(text_t* text);

void GetTextSymbols(text_t* text, FILE* input_file);
void ParseText(text_t* text);

error_t StringCtor(text_t* text, FILE* input_file);
void StringDtor(text_t* text);
void CopyStrings(string_t* dst, string_t* src, size_t str_cnt);

#endif /* TEXT_LIB_H */

