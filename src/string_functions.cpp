#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "string_functions.h"

void SkipNonAlphaSymbols(size_t* i, const string_t* str, sort_mode_t mode) {
    if (mode == FIRST) {
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

    SkipNonAlphaSymbols(&i, s1, FIRST);
    SkipNonAlphaSymbols(&j, s2, FIRST);

    while (i < s1->length - 1 && j < s2->length - 1 &&
           s1->begin[i] != '\0' &&
           tolower(s1->begin[i]) == tolower(s2->begin[j])) {
        i++;
        j++;

        SkipNonAlphaSymbols(&i, s1, FIRST);
        SkipNonAlphaSymbols(&j, s2, FIRST);
    }

    return (tolower(s1->begin[i]) > tolower(s2->begin[j]))  ? 1 :
           (tolower(s1->begin[i]) == tolower(s2->begin[j])) ? 0 : -1;
}

int CompareStringsBackward(const void *str1, const void *str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    const string_t* s1 = (const string_t*) str1;
    const string_t* s2 = (const string_t*) str2;

    size_t i = s1->length - 2;
    size_t j = s2->length - 2;

    SkipNonAlphaSymbols(&i, s1, LAST);
    SkipNonAlphaSymbols(&j, s2, LAST);

    while (i > 0 && j > 0 &&
           tolower(s1->begin[i]) == tolower(s2->begin[j])) {
        i--;
        j--;

        SkipNonAlphaSymbols(&i, s1, LAST);
        SkipNonAlphaSymbols(&j, s2, LAST);
    }

    return (tolower(s1->begin[i]) > tolower(s2->begin[j]))  ? 1 :
           (tolower(s1->begin[i]) == tolower(s2->begin[j])) ? 0 : -1;
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
    for (; i < n; i++) {
        uint32_t s = 0;
        memcpy(&s, (uint32_t*) s1 + i, sizeof(uint32_t));
        memcpy((uint32_t*) s1 + i, (uint32_t*) s2 + i, sizeof(uint32_t));
        memcpy((uint32_t*) s2 + i, &s, sizeof(uint32_t));

    }

    i *= 2;
    n = width / sizeof(uint16_t);
    width = width - n * sizeof(uint16_t);
    for (; i < n; i++) {
        uint16_t s = 0;
        memcpy(&s, (uint16_t*) s1 + i, sizeof(uint16_t));
        memcpy((uint16_t*) s1 + i, (uint16_t*) s2 + i, sizeof(uint16_t));
        memcpy((uint16_t*) s2 + i, &s, sizeof(uint16_t));
    }

    i *= 2;
    n = width / sizeof(uint8_t);
    width = width - n * sizeof(uint8_t);
    for (; i < n; i++) {
        uint8_t s = 0;
        memcpy(&s, (uint8_t*) s1 + i, sizeof(uint8_t));
        memcpy((uint8_t*) s1 + i, (uint8_t*) s2 + i, sizeof(uint8_t));
        memcpy((uint8_t*) s2 + i, &s, sizeof(uint8_t));
    }

    i *= 8;
    n = width / sizeof(char);
    width = width - n * sizeof(char);
    for (; i < n; i++) {
        char s = 0;
        memcpy(&s, (char*) s1 + i, sizeof(char));
        memcpy((char*) s1 + i, (char*) s2 + i, sizeof(char));
        memcpy((char*) s2 + i, &s, sizeof(char));
    }
}

