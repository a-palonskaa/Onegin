#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//SECTION - в алфавином порядке
#include "arg_parser.h"
#include "define_constants.h"
#include "print_results.h"
#include "sort.h"
#include "string_functions.h"
#include "text_t_lib.h"
#include "logger.h"

int main(int argc, const char* argv[]) {
    LoggerSetFile(stdout);
    LoggerSetLevel(DEBUG);

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

    if (flags.sort_mode_cnt) {
        text.sort_state = COMPLEX;
    }
    else {
        text.sort_state = DEFAULT;
    }

    if (StringCtor(&text, input_file) != NO_ERRORS) {
        return EXIT_FAILURE;
    }

    size_t str_cnt = text.strings_amount;
    size_t strint_t_size = sizeof(string_t);
    if (text.sort_state == COMPLEX) {
        for (size_t i = 1; i < SORT_TYPES_CNT; i++) {
            SortText(text.strings.sorted[i], str_cnt, strint_t_size, CompareStringsBackward, flags.sort_type);
        }
        PrintSortedText(output_file, &text, &flags);
    }
    else {
        SortText(text.strings.non_sorted, str_cnt, strint_t_size, CompareStringsBackward, flags.sort_type);
        fprintf(output_file, "\n\nBackward sorting:\n");
        PrintSortedText(output_file, &text, &flags);

        SortText(text.strings.non_sorted, str_cnt, strint_t_size, CompareStringsForward, flags.sort_type);
        fprintf(output_file, "\n\nForward sorting:\n");
        PrintSortedText(output_file, &text, &flags);

        PrintNonSortedText(output_file, &text);
    }

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

