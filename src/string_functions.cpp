#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "string_functions.h"
#include "define_constants.h"

void SkipNonAlphaSymbols(size_t* i, const string_t* str, sort_mode_t mode) {
    if (mode == FORWARD) {
        while(!isalpha(str->begin[*i]) && *i < str->length && str->begin[*i] != '\0') {
            (*i)++;
        }
    }
    else {
        while(!isalpha(str->begin[*i]) && *i > 0 && str->begin[*i] != '\0') {
            (*i)--;
        }
    }
}

int CompareStringsForward(const void *str1, const void *str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    const string_t* s1 = (const string_t*) str1;
    const string_t* s2 = (const string_t*) str2;

    size_t i = 0;
    size_t j = 0;

    SkipNonAlphaSymbols(&i, s1, FORWARD);
    SkipNonAlphaSymbols(&j, s2, FORWARD);

    while (i < s1->length - 1 && j < s2->length - 1 &&
           s1->begin[i] != '\0' &&
           tolower(s1->begin[i]) == tolower(s2->begin[j])) {
        i++;
        j++;

        SkipNonAlphaSymbols(&i, s1, FORWARD);
        SkipNonAlphaSymbols(&j, s2, FORWARD);
    }

    return tolower(s1->begin[i]) - tolower(s2->begin[j]);
}

int CompareStringsBackward(const void *str1, const void *str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    const string_t* s1 = (const string_t*) str1;
    const string_t* s2 = (const string_t*) str2;

    size_t i = s1->length - 2;
    size_t j = s2->length - 2;

    SkipNonAlphaSymbols(&i, s1, BACKWARD);
    SkipNonAlphaSymbols(&j, s2, BACKWARD);

    while (i > 0 && j > 0 &&
           tolower(s1->begin[i]) == tolower(s2->begin[j])) {
        i--;
        j--;

        SkipNonAlphaSymbols(&i, s1, BACKWARD);
        SkipNonAlphaSymbols(&j, s2, BACKWARD);
    }

    return tolower(s1->begin[i]) - tolower(s2->begin[j]);
}

void SwapStrings(void* s1, void* s2, size_t width) {
    size_t i = 0;

    size_t n = width / sizeof(uint64_t);
    width = width - n * sizeof(uint64_t);

    for (; i < n; i++) {
        uint64_t s = 0;
        memcpy(&s, (uint64_t*) s1 + i, sizeof(uint64_t));
        memcpy((uint64_t*) s1 + i, (uint64_t*) s2 + i, sizeof(uint64_t));
        memcpy((uint64_t*) s2 + i, &s, sizeof(uint64_t));
    }

    i *= 2;
    n = width / sizeof(uint32_t);
    width = width - n * sizeof(uint32_t);

    if (n) {
        uint32_t s = 0;
        memcpy(&s, (uint32_t*) s1 + i, sizeof(uint32_t));
        memcpy((uint32_t*) s1 + i, (uint32_t*) s2 + i, sizeof(uint32_t));
        memcpy((uint32_t*) s2 + i, &s, sizeof(uint32_t));
        i++;

    }

    i *= 2;
    n = width / sizeof(uint16_t);
    width = width - n * sizeof(uint16_t);

    if (n) {
        uint16_t s = 0;
        memcpy(&s, (uint16_t*) s1 + i, sizeof(uint16_t));
        memcpy((uint16_t*) s1 + i, (uint16_t*) s2 + i, sizeof(uint16_t));
        memcpy((uint16_t*) s2 + i, &s, sizeof(uint16_t));
        i++;
    }

    i *= 2;
    n = width / sizeof(uint8_t);
    width = width - n * sizeof(uint8_t);

    if (n) {
        uint8_t s = 0;
        memcpy(&s, (uint8_t*) s1 + i, sizeof(uint8_t));
        memcpy((uint8_t*) s1 + i, (uint8_t*) s2 + i, sizeof(uint8_t));
        memcpy((uint8_t*) s2 + i, &s, sizeof(uint8_t));
        i++;
    }
}

