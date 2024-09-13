#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_results.h"
#include "sort.h"
#include "text_t_lib.h"
#include "string_functions.h"
#include "arg_parser.h"

int main(int argc, const char *argv[]) {
    flags_t flags = {};
    InitiallizeFlags(&flags);

    if (ArgParser(argc, argv, &flags) == INPUT_ERROR) {
        return EXIT_FAILURE;
    }

    FILE* input_file  = fopen(flags.input_file_name, "r");

    if (input_file == nullptr) {
        perror("FAILED TO OPEN INPUT FILE\n");
        return EXIT_FAILURE;
    }

    FILE* output_file = fopen(flags.output_file_name, "w");

    if (output_file == nullptr) {
        perror("FAILED TO OPEN OUTPUT FILE\n");
        return EXIT_FAILURE;
    }

    text_t text = {};

    StringCtor(&text, input_file);

    if (flags.sort_mode == QUICK_SORT) {
        printf("Sort text with  quick sort\n");

        QuickSort(text.backward_sorted_strings, text.strings_amount, sizeof(string_t), CompareStringsBackward);
        QuickSort(text.forward_sorted_strings, text.strings_amount, sizeof(string_t), CompareStringsForward);
    }
    else {
        printf("Sort text with bubble sort\n");

        BubbleSort(text.backward_sorted_strings, text.strings_amount, sizeof(string_t), CompareStringsBackward);
        BubbleSort(text.forward_sorted_strings, text.strings_amount, sizeof(string_t), CompareStringsForward);
    }

    PrintSortedText(output_file, &text);

    StringDtor(&text);

    if(fclose(input_file) == EOF) {
        perror("FAILED TO CLOSE INPUT FILE\n");
        return EXIT_FAILURE;
    }

    if(fclose(output_file) == EOF) {
        perror("FAILED TO CLOSE OUTPUT FILE\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

