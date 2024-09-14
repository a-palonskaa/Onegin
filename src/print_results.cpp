#include <assert.h>
#include <string.h>

#include "print_results.h"

void PrintTextTestMode(FILE* output_file, text_t* text, sort_mode_t mode) {
    assert(output_file != nullptr);
    assert(text != nullptr);

    string_t* sorted_strings = nullptr;

    switch (mode) {
        case BACKWARD:
            fprintf(output_file, "\n\nBackward sorting:\n");
            sorted_strings  = text->backward_sorted_strings;
            break;
        case FORWARD:
            fprintf(output_file, "\n\nForward sorting:\n");
            sorted_strings  = text->forward_sorted_strings;
            break;
        case NO_SORT:
            fprintf(output_file, "\n\nInitial text:\n");
            sorted_strings  = text->nonsorted_strings;
            break;
        default:
            return;
    }

    for (size_t i = 0; i < text->strings_amount; i++) {
        fputs(sorted_strings[i].begin, output_file);
        fprintf(output_file, "\n");
    }
}

void PrintSortedText(FILE* output_file, text_t* text, flags_t* flags) {
    if (flags->sort_mode_cnt == 0) {
        for (size_t i = 0; i < flags->sort_mode_cnt_default; i++) {
            PrintTextTestMode(output_file, text, flags->sort_mode_default[i]);
        }
        return;
    }
    for (size_t i = 0; i < flags->sort_mode_cnt; i++) {
        PrintTextTestMode(output_file, text, flags->sort_mode[i]);
    }
}

void PrintNonSortedText(FILE* output_file, text_t* text) {
    fprintf(output_file, "\n\nInitial sorting:\n");

    for (size_t i = 0; i < text->symbols_amount; i++) {
        if (text->symbols[i] == '\0') {
            text->symbols[i] = '\n';
        }
    }

    fwrite(text->symbols, sizeof(char), text->symbols_amount, output_file);

    for (size_t i = 0; i < text->symbols_amount; i++) {
        if (text->symbols[i] == '\n') {
            text->symbols[i] = '\0';
        }
    }
}

