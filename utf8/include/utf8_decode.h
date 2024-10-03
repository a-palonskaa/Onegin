#ifndef UTF8_DECODE_H
#define UTF8_DECODE_H

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

const uint32_t FIRST_BIT_ZERO_MASK = 0x80000000;
const uint32_t LAST_SIX_BITS_MASK = 0x3F;

typedef enum {
    NOERRORS           = 0,
    LENGTH_ENCODE_ERROR = 1,
    END_OF_FILE         = 2,
    POISON_VALUE        = 3
} errors_t;

errors_t ReadOctetsUTF8(my_rune_t* rune, unsigned char* buffer);
uint32_t DecodeSymbolUTF8(my_rune_t* rune);
void PrintSymbolUTF8(my_rune_t* rune, FILE* outstream);
size_t EncodeSymbolUTF8(uint32_t code, char* buffer);

#endif /* UTF8_DECODE_H */
