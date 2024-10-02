#ifndef UTF8_TEXT_H
#define UTF8_TEXT_H

#include <stdio.h>

#include "utf8_decode.h"

typedef enum {
    NO_ERRORS                     = 0,
    FILE_READ_ERROR               = 1,
    MEMORY_ALLOCATE_ERROR         = 2,
    INFILE_PTR_MOVING_ERROR       = 3,
    EMPTY_FILE_ERROR              = 4,
    PTR_POSITION_INDICATION_ERROR = 5,
} error_t;

error_t StringCtor(text_t* text, FILE* input_file);
void StringDtor(text_t* text);

errors_t ReadStrings(string_t* text, FILE* instream);
void ReadText(text_t* text, FILE* instream);

#endif /* UTF8_TEXT_H */
