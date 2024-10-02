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

ssize_t FindFileSize(FILE* input_file);
size_t ReadStrings(text_t* text, size_t string_cnt, size_t in_bytes_cnt, FILE* instream);
void ParseText(text_t* text, FILE* instream);

#endif /* UTF8_TEXT_H */
