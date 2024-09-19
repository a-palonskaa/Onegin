#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "includes_sort.h"
#include "sort.h"

void SortIncludes(text_t* text, FILE* output_file) {
    const char* system_include = "include <";
    const char* user_include = "include \"";

    include_strings_t user_header_files[50] = {};  //""
    include_strings_t system_includes[50]   = {};  //<>

    size_t i = 0, j = 0, k = 0;

    for (; i < text->strings_amount; i++) {
        char* ptr = strstr(text->strings.non_sorted[i].begin, system_include);

        if (ptr != nullptr) {
            system_includes[j].include_name = ptr;
            system_includes[j++].string = text->strings.non_sorted[i];
            text->strings.non_sorted[i].begin = nullptr;
        }
        else {
            ptr = strstr(text->strings.non_sorted[i].begin, user_include);
            if (ptr != nullptr) {
                user_header_files[k].include_name = ptr;
                user_header_files[k++].string = text->strings.non_sorted[i];
                text->strings.non_sorted[i].begin = nullptr;
            }
        }
    }

    size_t system_includes_len = j;
    size_t user_header_files_len = k;

    QuickSort(system_includes, system_includes_len, sizeof(*system_includes), CompareIncludes);
    QuickSort(user_header_files, user_header_files_len, sizeof(*user_header_files), CompareIncludes);

    for (size_t cnt = 0; cnt < system_includes_len; cnt++) {
        fputs(system_includes[cnt].string.begin, output_file);
        fprintf(output_file, "\n");
    }

    fprintf(output_file, "\n");

    for (size_t cnt = 0; cnt < user_header_files_len; cnt++) {
        fputs(user_header_files[cnt].string.begin, output_file);
        fprintf(output_file, "\n");
    }

    for (size_t cnt = 0; cnt < text->strings_amount; cnt++) {
        if (text->strings.non_sorted[cnt].begin != nullptr) {
            fputs(text->strings.non_sorted[cnt].begin, output_file);
            fprintf(output_file, "\n");
        }
    }
}

int CompareIncludes(const void* str1, const void* str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    const include_strings_t* s1 = (const include_strings_t*) str1;
    const include_strings_t* s2 = (const include_strings_t*) str2;

    size_t i = 0;
    size_t j = 0;

    while (s1->include_name[i] != '.' && (tolower(s1->include_name[i]) == tolower(s2->include_name[j]))) {
        i++;
        j++;
    }

    return tolower(s1->include_name[i]) - tolower(s2->include_name[j]);
}
