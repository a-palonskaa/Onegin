#include <assert.h>
#include <ctype.h>

#include "string_functions.h"

static void SkipNonAlphaSymbols(int* i, int*j, const char* string1, const char* string2);

bool CompareStr(char* string1, char* string2) {
    assert(string1 != nullptr);
    assert(string2 != nullptr);

    int i = 0;
    int j = 0;

    SkipNonAlphaSymbols(&i, &j, string1, string2);

    while (i < MAX_STR_LEN && j < MAX_STR_LEN &&
           string1[i] != '\0' && tolower(string1[i]) == tolower(string2[j])) {
        i++;
        j++;
        SkipNonAlphaSymbols(&i, &j, string1, string2);
    }

    return (tolower(string1[i]) > tolower(string2[j]));
}

void SwapStr(char* string1, char* string2) {
    assert(string1 != nullptr);
    assert(string2 != nullptr);

    char c = 0;

    for (int i = 0; i < MAX_STR_LEN && (string1[i] != 0 || string2[i] != 0); i++) {
        c = string1[i];
        string1[i] = string2[i];
        string2[i] = c;
    }
}

static void SkipNonAlphaSymbols(int* i, int*j, const char* string1, const char* string2) {
    while(!isalpha(string1[*i]) && *i < MAX_STR_LEN && string1[*i] != '\0') {
        (*i)++;
    }
    while(!isalpha(string2[*j]) && *j < MAX_STR_LEN && string2[*j] != '\0') {
        (*j)++;
    }
}
