#include <assert.h>
#include <ctype.h>

#include "string_functions.h"

static void SkipNonAlphaSymbols(size_t* i, const char* str, sort_mode_t mode);

bool CompareStringsForward(size_t s1, size_t s2, string_t* text_strdata) {
    assert(text_strdata != nullptr);

    size_t i = 0;
    size_t j = 0;

    SkipNonAlphaSymbols(&i, text_strdata[s1].begin, FIRST);
    SkipNonAlphaSymbols(&j, text_strdata[s2].begin, FIRST);

    while (i < text_strdata[s1].length - 1 && j < text_strdata[s2].length - 1 &&
           text_strdata[s1].begin[i] != '\0' &&
           tolower(text_strdata[s1].begin[i]) == tolower(text_strdata[s2].begin[j])) {
        i++;
        j++;

        SkipNonAlphaSymbols(&i, text_strdata[s1].begin, FIRST);
        SkipNonAlphaSymbols(&j, text_strdata[s2].begin, FIRST);
    }

    return (tolower(text_strdata[s1].begin[i]) > tolower(text_strdata[s2].begin[j]));
}

void SwapStrings(size_t s1, size_t s2, string_t* text_strdata) {
    assert(text_strdata != nullptr);

    string_t strdata_s1_copy = text_strdata[s1];
    text_strdata[s1] = text_strdata[s2];
    text_strdata[s2] = strdata_s1_copy;
}

static void SkipNonAlphaSymbols(size_t* i, const char* str, sort_mode_t mode) {
    if (mode == FIRST) {
        while(!isalpha(str[*i]) && *i < MAX_STR_LEN && str[*i] != '\0') {
            (*i)++;
        }
    }
    else {
        while(!isalpha(str[*i]) && *i < MAX_STR_LEN && str[*i] != '\0') {
            (*i)--;
        }
    }
}

bool CompareStringsBackward(size_t s1, size_t s2, string_t* text_strdata) {
    assert(text_strdata != nullptr);

    size_t i = text_strdata[s1].length - 2;
    size_t j = text_strdata[s2].length - 2;

    SkipNonAlphaSymbols(&i, text_strdata[s1].begin, LAST);
    SkipNonAlphaSymbols(&j, text_strdata[s2].begin, LAST);

    while (i > 0 && j > 0 &&
           tolower(text_strdata[s1].begin[i]) == tolower(text_strdata[s2].begin[j])) {
        i--;
        j--;

        SkipNonAlphaSymbols(&i, text_strdata[s1].begin, LAST);
        SkipNonAlphaSymbols(&j, text_strdata[s2].begin, LAST);
    }

    return (tolower(text_strdata[s1].begin[i]) > tolower(text_strdata[s2].begin[j]));
}

