#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "string_functions.h"
#include "define_constants.h"

void SkipNonAlphaSymbols(const string_t* str, size_t* i, sort_mode_t mode) {
    if (mode == FORWARD) {
        while (!isalpha(str->begin[*i]) && *i < str->length && str->begin[*i] != '\0') {
            (*i)++;
        }
    }
    else {
        while (!isalpha(str->begin[*i]) && *i > 0 && str->begin[*i] != '\0') {
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
           s1->begin[i] != '\0' &&
           tolower(s1->begin[i]) == tolower(s2->begin[j])) {
        i++;
        j++;

        SkipNonAlphaSymbols(s1, &i, FORWARD);
        SkipNonAlphaSymbols(s2, &j, FORWARD);
    }

    return tolower(s1->begin[i]) - tolower(s2->begin[j]);
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
           tolower(s1->begin[i]) == tolower(s2->begin[j])) {
        i--;
        j--;

        SkipNonAlphaSymbols(s1, &i, BACKWARD);
        SkipNonAlphaSymbols(s2, &j, BACKWARD);
    }

    return tolower(s1->begin[i]) - tolower(s2->begin[j]);
}
