#include <assert.h>
#include <ctype.h>

#include "string_functions.h"

static void SkipNonAlphaSymbols(size_t* s1, size_t* s2, const char* string1, const char* string2);

bool CompareStr(size_t s1, size_t s2, strdata_t* text_strdata) {
    assert(text_strdata != nullptr);

    size_t i = 0;
    size_t j = 0;

    SkipNonAlphaSymbols(&i, &j, text_strdata[s1].str_begin, text_strdata[s2].str_begin);

    while (i < text_strdata[s1].str_len - 1 && j < text_strdata[s2].str_len - 1 &&
           text_strdata[s1].str_begin[i] != '\0' &&
           tolower(text_strdata[s1].str_begin[i]) == tolower(text_strdata[s2].str_begin[j])) {
        i++;
        j++;

        SkipNonAlphaSymbols(&i, &j, text_strdata[s1].str_begin, text_strdata[s2].str_begin);
    }

    return (tolower(text_strdata[s1].str_begin[i]) > tolower(text_strdata[s2].str_begin[j]));
}

void SwapStr(size_t s1, size_t s2, strdata_t* text_strdata) {
    assert(text_strdata != nullptr);

    strdata_t strdata_s1_copy = text_strdata[s1];
    text_strdata[s1] = text_strdata[s2];
    text_strdata[s2] = strdata_s1_copy;
}

static void SkipNonAlphaSymbols(size_t* i, size_t* j, const char* string1, const char* string2) {
    while(!isalpha(string1[*i]) && *i < MAX_STR_LEN && string1[*i] != '\0') {
        (*i)++;
    }
    while(!isalpha(string2[*j]) && *j < MAX_STR_LEN && string2[*j] != '\0') {
        (*j)++;
    }
}
