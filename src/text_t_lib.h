#ifndef TEXT_T_LIB_H
#define TEXT_T_LIB_H

#include <stdio.h>

typedef struct {
    char* begin;
    size_t length;
} string_t;

typedef struct {
    size_t symbols_amount;
    size_t strings_amount;
    string_t* nonsorted_strings;
    string_t* forward_sorted_strings;
    string_t* backward_sorted_strings;
    char* symbols;
} text_t;

typedef enum {
    NO_ERRORS               = 0,
    FILE_READ_ERROR         = 1,
    MEMORY_ALLOCATE_ERROR   = 2,
    INFILE_PTR_MOVING_ERROR = 3,
    EMPTY_FILE_ERROR        = 4
} error_t;

ssize_t CountTextSymbolsTest(FILE* input_file);
ssize_t CountTextSymbols(FILE* input_file);
size_t CountTextLines(text_t* text);

void GetTextSymbols(text_t* text, FILE* input_file);
void IndexStrings(text_t* text);

error_t StringCtor(text_t* text, FILE* input_file);
void StringDtor(text_t* text);

// BIOS

#endif /* TEXT_T_LIB_H */

