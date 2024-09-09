#include <assert.h>
#include <ctype.h>

#include "string_functions.h"

static void SkipNonAlphaSymbols(size_t* s1, size_t* s2, const char* string1, const char* string2, sort_mode_t mode);

bool CompareStrFirst(size_t s1, size_t s2, str_store_data_t* text_strdata) {
    assert(text_strdata != nullptr);

    size_t i = 0;
    size_t j = 0;

    SkipNonAlphaSymbols(&i, &j, text_strdata[s1].str_begin, text_strdata[s2].str_begin, FIRST);

    while (i < text_strdata[s1].str_len - 1 && j < text_strdata[s2].str_len - 1 &&
           text_strdata[s1].str_begin[i] != '\0' &&
           tolower(text_strdata[s1].str_begin[i]) == tolower(text_strdata[s2].str_begin[j])) {
        i++;
        j++;

        SkipNonAlphaSymbols(&i, &j, text_strdata[s1].str_begin, text_strdata[s2].str_begin, FIRST);
    }

    return (tolower(text_strdata[s1].str_begin[i]) > tolower(text_strdata[s2].str_begin[j]));
}

void SwapStr(size_t s1, size_t s2, str_store_data_t* text_strdata) {
    assert(text_strdata != nullptr);

    str_store_data_t strdata_s1_copy = text_strdata[s1];
    text_strdata[s1] = text_strdata[s2];
    text_strdata[s2] = strdata_s1_copy;
}

static void SkipNonAlphaSymbols(size_t* i, size_t* j, const char* string1, const char* string2, sort_mode_t mode) {
    while(!isalpha(string1[*i]) && *i < MAX_STR_LEN && string1[*i] != '\0') {
        if (mode == FIRST) {
            (*i)++;
        }
        else {
            (*i)--;
        }
    }
    while(!isalpha(string2[*j]) && *j < MAX_STR_LEN && string2[*j] != '\0') {
        if (mode == FIRST) {
            (*j)++;
        }
        else {
            (*j)--;
        }
    }
}

bool CompareStrLast(size_t s1, size_t s2, str_store_data_t* text_strdata) {
        assert(text_strdata != nullptr);

    size_t i = text_strdata[s1].str_len - 2;
    size_t j = text_strdata[s2].str_len - 2;

    SkipNonAlphaSymbols(&i, &j, text_strdata[s1].str_begin, text_strdata[s2].str_begin, LAST);

    while (i > 0 && j > 0 &&
           tolower(text_strdata[s1].str_begin[i]) == tolower(text_strdata[s2].str_begin[j])) {
        i--;
        j--;

        SkipNonAlphaSymbols(&i, &j, text_strdata[s1].str_begin, text_strdata[s2].str_begin, LAST);
    }

    return (tolower(text_strdata[s1].str_begin[i]) > tolower(text_strdata[s2].str_begin[j]));
}
