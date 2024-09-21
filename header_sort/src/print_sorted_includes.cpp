#include "print_sorted_includes.h"

void PrintSortedIncludes(text_t* text, FILE* output_file) {
    for (size_t cnt = 0; cnt < text->strings_amount; cnt++) {
        fputs(text->strings.non_sorted[cnt].begin, output_file);
        fprintf(output_file, "\n");
    }
}
