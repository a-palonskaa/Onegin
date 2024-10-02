#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "string_functions.h"

void SkipNonAlphaSymbols(const string_t* str, size_t* i, sort_mode_t mode) {
    if (mode == FORWARD) {
        while (!IsAlphaUtf8(str->runes[*i]) && *i < str->length && str->runes[*i] != 0xA) {
            (*i)++;
        }
    }
    else {
        while (!IsAlphaUtf8(str->runes[*i]) && *i > 0 && str->runes[*i] != 0xA) {
            (*i)--;
        }
    }
}

int CompareStringsForward(const void* str1, const void* str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    const string_t* s1 = (const string_t*) str1;
    const string_t* s2 = (const string_t*) str2;

    size_t i = 0;
    size_t j = 0;

    SkipNonAlphaSymbols(s1, &i, FORWARD);
    SkipNonAlphaSymbols(s2, &j, FORWARD);

    while (i < s1->length - 1 && j < s2->length - 1 &&
           s1->runes[i] != 0xA &&
           ToLowerUTF8(s1->runes[i]) == ToLowerUTF8(s2->runes[j])) {
        i++;
        j++;

        SkipNonAlphaSymbols(s1, &i, FORWARD);
        SkipNonAlphaSymbols(s2, &j, FORWARD);
    }
    return (int) (ToLowerUTF8(s1->runes[i]) - ToLowerUTF8(s2->runes[j]));
}

int CompareStringsBackward(const void* str1, const void* str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    const string_t* s1 = (const string_t*) str1;
    const string_t* s2 = (const string_t*) str2;

    size_t i = s1->length - 2;
    size_t j = s2->length - 2;

    SkipNonAlphaSymbols(s1, &i, BACKWARD);
    SkipNonAlphaSymbols(s2, &j, BACKWARD);

    while (i > 0 && j > 0 &&
           ToLowerUTF8(s1->runes[i]) == ToLowerUTF8(s2->runes[j])) {
        i--;
        j--;

        SkipNonAlphaSymbols(s1, &i, BACKWARD);
        SkipNonAlphaSymbols(s2, &j, BACKWARD);
    }

    return (int) (ToLowerUTF8(s1->runes[i]) - ToLowerUTF8(s2->runes[j]));
}

bool IsAlphaUtf8(uint32_t code) {
    if (code >= 0x410 && code <= 0x4FF) {
        return true;
    }
    return false;
}

uint32_t ToLowerUTF8(uint32_t code) {
    if (code >= 0x410 && code <= 0x42F) {
        return code + 0x20;
    }
    else if (code >= 0x430 && code <= 0x4FF) {
        return code;
    }
    return code;
}
//FIXME - maybe by fread read all symbols and then work with char* buffer
