#include <assert.h>

#include "utf8_decode.h"

static errors_t CountOctetsUTF8(my_rune_t* rune);

static errors_t CountOctetsUTF8(my_rune_t* rune) {
    assert(rune != nullptr);
    uint32_t bits = rune->bits;
    size_t cnt = 0;

    if (!(bits & FIRST_BIT_ZERO_MASK)) {
        rune->width = ++cnt;
        return NOERRORS;
    }

    cnt++;
    while (((bits << 1) & FIRST_BIT_ZERO_MASK) && (cnt < 4)) {
        bits = bits << 1;
        cnt++;
    }

    if (cnt == 4 && ((bits << 1) & FIRST_BIT_ZERO_MASK)) {
        rune->width = 0;
        return LENGTH_ENCODE_ERROR;
    }
    rune->width = cnt;

    return NOERRORS;
}


errors_t ReadOctetsUTF8(my_rune_t* rune, unsigned char* buffer) {
    assert(rune != nullptr);
    assert(buffer != nullptr);

    unsigned char c = buffer[0];
    rune->bits = (uint32_t) c << 24;

    if (CountOctetsUTF8(rune) != NOERRORS) {
        return LENGTH_ENCODE_ERROR;
    }

    for (size_t i = 2; i <= rune->width; i++) {
        c = buffer[i - 1];
        rune->bits = rune->bits + ((uint32_t) c << (8 * (4 - i)));
    }
    return NOERRORS;
}

uint32_t DecodeSymbolUTF8(my_rune_t* rune) {
    assert(rune != nullptr);
    uint32_t bits = rune->bits;
    uint32_t code = 0;

    bits = bits >> (8 * (4 - rune->width));

    for (size_t i = 0; i < rune->width - 1; i++) {
        code += (bits & LAST_SIX_BITS_MASK) << (6 * i);

        bits = bits >> 8;
    }

    code += ((0xFF >> rune->width) & bits) << (6 * (rune->width - 1));
    rune->code = code;
    return code;
}

void PrintSymbolUTF8(my_rune_t* rune, FILE* outstream) {
    for (size_t i = 0; i < rune->width; i++) {
        fputc((unsigned char) ((rune->bits) >> (8 * (3 - i))), outstream);
    }
}

size_t EncodeSymbolUTF8(uint32_t code, char* buffer) {
    size_t width = 0;

    if (code <= 0x7F) {
        width = 1;
        buffer[0] = (char) code;
    }
    else if (code <= 0x7FF) {
        width = 2;
        buffer[0] = (char) (0xC0 | (code >> 6));
        buffer[1] = (char) (0x80 | (code & 0x3F));
    }
    else if (code <= 0xFFFF) {
        width = 3;
        buffer[0] = (char) (0xE0 | (code >> 12));
        buffer[1] = (char) (0x80 | ((code >> 6) & 0x3F));
        buffer[2] = (char) (0x80 | (code & 0x3F));
    }
    else if (code <= 0x10FFFF) {
        width = 4;
        buffer[0] = (char) (0xF0 | (code >> 18));
        buffer[1] = (char) (0x80 | ((code >> 12) & 0x3F));
        buffer[2] = (char) (0x80 | ((code >> 6) & 0x3F));
        buffer[3] = (char) (0x80 | (code & 0x3F));
    }
    return width;
}
