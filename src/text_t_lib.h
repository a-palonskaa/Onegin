#ifndef TEXT_INF_LIB_H //ХУЙНЯ - rename lib (XXinfXX)
#define TEXT_INF_LIB_H

#include <stdio.h>

typedef struct {
    char* begin;
    size_t length;
} string_t;

typedef struct {
    size_t symbols_amount;
    size_t strings_amount;
    string_t* strings;
    char* symbols;
} text_t;

typedef enum {
    NO_ERRORS               = 0,
    FILE_READ_ERROR         = 1,
    MEMORY_ALLOCATE_ERROR   = 2,
    INFILE_PTR_MOVING_ERROR = 3
} error_t;

size_t CountTextSymbols(FILE* input_file);
size_t CountTextLines(text_t* text);
void IndexStrings(text_t* text);
error_t StringCtor(text_t* text, FILE* input_file);
void GetTextSymbols(text_t* text, FILE* input_file);
void StringDtor(text_t* text);

// BIOS

#endif /* TEXT_INF_LIB_H */

