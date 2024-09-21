#include <assert.h>
#include <string.h>

#include "print_results.h"

void PrintTextTestMode(FILE* output_file, text_t* text, const sort_mode_t mode) {
    assert(output_file != nullptr);
    assert(text != nullptr);

    string_t* sorted_strings = nullptr;

    switch (mode) {
        case BACKWARD:
            fprintf(output_file, "\n\nBackward sorting:\n");
            sorted_strings  = text->strings.sorted[1];
            break;
        case FORWARD:
            fprintf(output_file, "\n\nForward sorting:\n");
            sorted_strings  = text->strings.sorted[2];
            break;
        case NO_SORT:
            fprintf(output_file, "\n\nInitial text:\n");
            sorted_strings  = text->strings.sorted[0];
            break;
        default:
            return;
    }

    for (size_t i = 0; i < text->strings_amount; i++) {
        fputs(sorted_strings[i].begin, output_file);

        if (*(sorted_strings[i].begin) != '\0') {
            fprintf(output_file, "\n");
        }
    }
}

void PrintSortedText(FILE* output_file, text_t* text, flags_t* flags) {
    if (text->sort_state == DEFAULT) {
        for (size_t i = 0; i < text->strings_amount; i++) {
            fputs(text->strings.non_sorted[i].begin, output_file);
            if (*(text->strings.non_sorted[i].begin) != '\0') {
                fprintf(output_file, "\n");
            }
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

