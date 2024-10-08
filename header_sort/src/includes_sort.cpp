#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "includes_sort.h"
#include "sort.h"
#include "text_lib.h"
#include "logger.h"
#include "define_colors.h"

void SortIncludes(text_t* text) {
    assert(text != nullptr);

    const char* INCLUDE = "#include";
    char* ptr = nullptr;
    size_t counter = 0, includes_sequence_len = 0;

    for (;counter < text->strings_amount - 1; counter++) {
        ptr = strstr(text->strings.non_sorted[counter].begin, INCLUDE);
        if (ptr == nullptr) {
            continue;
        }

        ptr = strstr(text->strings.non_sorted[counter + 1].begin, INCLUDE);
        if (ptr == nullptr) {
            continue;
        }

        includes_sequence_len = 2;
        counter++;

        while (++counter < text->strings_amount &&
               (ptr = strstr(text->strings.non_sorted[counter].begin, INCLUDE)) != nullptr) {
            includes_sequence_len++;
        }

        QuickSort((&text->strings.non_sorted[0] + counter - includes_sequence_len),
                    includes_sequence_len, sizeof(string_t), CompareIncludes);
    }
    Log(INFO, "SUCCESSFULLY SORTED INCLUDES\n");
}

int CompareIncludes(const void* str1, const void* str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    const string_t* s1 = (const string_t*) str1;
    const string_t* s2 = (const string_t*) str2;

    size_t i = 0;

    while (i < s1->length - 1 && i < s2->length - 1 &&
           s1->begin[i] != '\0' &&
           tolower(s1->begin[i]) == tolower(s2->begin[i])) {
        i++;
    }

    if ((s1->begin[i] == '<' && s2->begin[i] == '"' ) ||
        (s1->begin[i] == '"' && s2->begin[i] == '<')) {
        return s2->begin[i] - s1->begin[i];
    }
    return tolower(s1->begin[i]) - tolower(s2->begin[i]);
}
