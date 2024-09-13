#include <assert.h>

#include "print_results.h"

void PrintTextTestMode(FILE* output_file, text_t* text, sort_mode_t mode) {
    assert(output_file != nullptr);
    assert(text != nullptr);

    string_t* sorted_strings = nullptr;

    switch (mode) {
        case BACKWARD:
            sorted_strings  = text->backward_sorted_strings;
            break;
        case FORWARD:
            sorted_strings  = text->forward_sorted_strings;
            break;
        case NO_SORT:
            sorted_strings  = text->nonsorted_strings;
            break;
        default:
            return;
    }

    for (size_t i = 0; i < text->strings_amount; i++) {
        for (size_t j = 0; j < sorted_strings[i].length - 1; j++) {
            fprintf(output_file, "%c", sorted_strings[i].begin[j]);
        }

        fprintf(output_file, "\n");
    }

}

void PrintSortedText(FILE* output_file, text_t* text) {
    fprintf(output_file, "Initial text:\n");
    PrintTextTestMode(output_file, text, NO_SORT);

    fprintf(output_file, "\n\nBackward sorting:\n");
    PrintTextTestMode(output_file, text, BACKWARD);

    fprintf(output_file, "\n\nForward sorting:\n");
    PrintTextTestMode(output_file, text, FORWARD);
}
