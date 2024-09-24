#ifndef UTF8_DECODE_H
#define UTF8_DECODE_H

#include <stdio.h>
#include <stdlib.h>

#include "define_consts.h"

const uint32_t FIRST_BIT_ZERO_MASK = 0x80000000;
const uint32_t LAST_SIX_BITS_MASK = 0x3F;

typedef enum {
    NO_ERRORS           = 0,
    LENGTH_ENCODE_ERROR = 1,
    END_OF_FILE         = 2
} error_t;

error_t ReadOctetsUTF8(my_rune_t* rune, FILE* stream);
uint32_t DecodeSymbolUTF8(my_rune_t* rune);
void PrintSymbolUTF8(my_rune_t* rune, FILE* outstream);

#endif /* UTF8_DECODE_H */
