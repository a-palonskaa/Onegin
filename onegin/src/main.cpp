#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "define_constants.h"
#include "text_lib.h"
#include "logger.h"
#include "sort_and_print.h"
#include "sort.h"
#include "print_results.h"
#include "parse_arguments.h"
#include "string_functions.h"
#include "onegin_argparser.h"

int main(int argc, const char* argv[]) {
    flags_t flags = {};
    InitiallizeFlagsOnegin(&flags);

    if (ArgParser(argc, argv, &flags, COMMANDS, CMD_ARRAY_LENGTH, &ValidateInput) == INPUT_ERROR) {
        return EXIT_FAILURE;
    }

    FILE* logger_output = (!strcmp(flags.logger_output_file, "stdout")) ?
                        stdout : (!strcmp(flags.logger_output_file, "stderr")) ?
                        stderr : fopen(flags.logger_output_file, "w");

    if (logger_output== nullptr) {
        perror("FAILED TO OPEN LOGGER OUTPUT FILE");
        logger_output = stderr;
    }

    LoggerSetLevel(DEBUG);
    LoggerSetFile(logger_output);

    FILE* input_file  = (!strcmp(flags.input_file_name, "stdin")) ?
                          stdin : fopen(flags.input_file_name, "r");
    if (input_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN INPUT FILE\n" STRERROR(errno));
        return EXIT_FAILURE;
    }

    FILE* output_file = (!strcmp(flags.output_file_name, "stdout")) ?
                          stdout : fopen(flags.output_file_name, "w");
    if (output_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN OUTPUT FILE\n" STRERROR(errno));
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

    bool empty_file_flag = false;
    if (text.symbols_amount == 1 || text.strings_amount == 0) {
        printf("EMPTY FILE\n");
        empty_file_flag = true;
    }

    if (!empty_file_flag) {
        SortAndPrintText(&text, &flags, output_file);
    }

    StringDtor(&text);

    if (fclose(input_file) == EOF) {
        Log(ERROR, "FAILED TO CLOSE INPUT FILE\n" STRERROR(errno));
        return EXIT_FAILURE;
    }

    if (fclose(output_file) == EOF) {
        Log(ERROR, "FAILED TO CLOSE OUTPUT FILE\n" STRERROR(errno));
        return EXIT_FAILURE;
    }

    if (fclose(logger_output) == EOF) {
        perror("FAILED TO CLOSE OUTPUT FILE\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
