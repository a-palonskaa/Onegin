#include <assert.h>
#include <ctype.h>

#include "string_functions.h"

bool CompareStr(char* string1, char* string2) {
    assert(string1 != nullptr);
    assert(string2 != nullptr);

    int i = 0;

    for (; i < MAX_STR_LEN && string1[i] != '\0' && tolower(string1[i]) == tolower(string2[i]); i++) {
        ;
    }
    return (string1[i] > string2[i]);
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
