#include "sort_and_print.h"
#include "sort.h"
#include "print_results.h"
#include "string_functions.h"

void SortAndPrintText(text_t* text, flags_t* flags, FILE* output_file) {
    const size_t str_cnt = text->strings_amount;
    const size_t strint_t_size = sizeof(string_t);

    if (text->sort_state == COMPLEX) {
        for (size_t i = 1; i < SORT_TYPES_CNT; i++) {
            SortText(text->strings.sorted[i], str_cnt, strint_t_size, CompareStringsBackward, flags->sort_type);
        }
        PrintSortedText(output_file, text, flags);
    }
    else {
        SortText(text->strings.non_sorted, str_cnt, strint_t_size, CompareStringsBackward, flags->sort_type);
        fprintf(output_file, "\n\nBackward sorting:\n");
        PrintSortedText(output_file, text, flags);

        SortText(text->strings.non_sorted, str_cnt, strint_t_size, CompareStringsForward, flags->sort_type);
        fprintf(output_file, "\n\nForward sorting:\n");
        PrintSortedText(output_file, text, flags);

        PrintNonSortedText(output_file, text);
    }
}
