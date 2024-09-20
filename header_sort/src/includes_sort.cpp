#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "includes_sort.h"
#include "sort.h"
#include "text_t_lib.h"
#include "string_functions.h"

void SortIncludes(text_t* text, FILE* output_file) {
    const char* INCLUDE = "#include";

    size_t counter = 0, includes_sequence_len = 0;

    for (; counter < text->strings_amount - 1; counter++) {
        char* ptr = strstr(text->strings.non_sorted[counter].begin, INCLUDE);
        if (ptr != nullptr) {
            ptr = strstr(text->strings.non_sorted[counter + 1].begin, INCLUDE);
            if (ptr != nullptr) {
                includes_sequence_len = 2;
                counter++;
                while (++counter < text->strings_amount &&
                      ((ptr = strstr(text->strings.non_sorted[counter].begin, INCLUDE)) != nullptr)) {
                        includes_sequence_len++;
                    }
                printf("START SORT = %d, END SORT = %d\n", counter - includes_sequence_len, counter);
                QuickSort((&text->strings.non_sorted[0] + counter - includes_sequence_len), includes_sequence_len, sizeof(string_t),
                           CompareIncludes);
            }
        }
    }
    for (size_t cnt = 0; cnt < text->strings_amount; cnt++) {
        fputs(text->strings.non_sorted[cnt].begin, output_file);
        fprintf(output_file, "\n");
    }
}

int CompareIncludes(const void* str1, const void* str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    const string_t* s1 = (const string_t*) str1;
    const string_t* s2 = (const string_t*) str2;

    size_t i = 0;
    size_t j = 0;

    while (i < s1->length - 1 && j < s2->length - 1 &&
           s1->begin[i] != '\0' &&
           tolower(s1->begin[i]) == tolower(s2->begin[j])) {
        i++;
        j++;
    }
    printf("SYMBOL = %c, END SYMBOL = %c\n", s1->begin[i], s2->begin[j]);
    if (s1->begin[i] == '<' && s2->begin[i] == '"') {
        return s2->begin[j] - s1->begin[i];
    }
    else if (s1->begin[i] == '"' && s2->begin[i] == '<') {
        printf("meow)\n");
        return s2->begin[j] - s1->begin[i];
    }
    printf("SYMBOL = %c, END SYMBOL = %c\n", s1->begin[i], s2->begin[j]);
    return tolower(s1->begin[i]) - tolower(s2->begin[j]);
}
