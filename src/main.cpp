#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arg_parser.h"
#include "define_constants.h"
#include "logger.h"
#include "print_results.h"
#include "sort.h"
#include "sort_and_print.h"
#include "string_functions.h"
#include "text_t_lib.h"
//ХУЙНЯ - добавить файл для логера и в аргументы командной строки чтобиожно было записфвать имя файла
// ХУЙНЯ: add const in all definitions but no decls
const char* LOGGER_OUTPUT = "./output/info";

int main(int argc, const char* argv[]) {
    FILE* logger_output_file = fopen(LOGGER_OUTPUT, "w");

    if (logger_output_file == nullptr) {
        perror("FAILED TO OPEN LOGGER OUTPUT FILE");
        logger_output_file = stdout;
    }

    LoggerSetLevel(DEBUG);
    LoggerSetFile(logger_output_file);

    flags_t flags = {};
    InitiallizeFlags(&flags);

    if (ArgParser(argc, argv, &flags) == INPUT_ERROR) {
        return EXIT_FAILURE;
    }

    FILE* input_file  = fopen(flags.input_file_name, "r");
    if (input_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN INPUT FILE\n", STRERROR(errno));
        return EXIT_FAILURE;
    }

    FILE* output_file = fopen(flags.output_file_name, "w");
    if (output_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN OUTPUT FILE\n", STRERROR(errno));
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

    // ХУЙНЯ: add func
    SortAndPrintText(&text, &flags, output_file);

    StringDtor(&text);

    if (fclose(input_file) == EOF) {
        Log(ERROR, "FAILED TO CLOSE INPUT FILE\n", STRERROR(errno));
        return EXIT_FAILURE;
    }

    if (fclose(output_file) == EOF) {
        Log(ERROR, "FAILED TO CLOSE OUTPUT FILE\n", STRERROR(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// TODO
//    /
//     build/
//         /...
//     common/
//         include/
//         src/
//         makefile
//     onegin/
//         include/
//         src/
//         makefile
//     header_sort/
//         include/
//         src/
//         makefile
//     makefile

// TODO: another layout: rle
