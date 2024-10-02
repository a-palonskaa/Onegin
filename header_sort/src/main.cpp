#include <stdio.h>
#include <stdlib.h>

#include "define_constants.h"
#include "includes_sort.h"
#include "sort.h"
#include "text_lib.h"
#include "logger.h"
#include "print_sorted_includes.h"

int main(int argc, const char* argv[]) {
    flags_t flags = {};
    InitiallizeFlagsHeaderSort(&flags);

    size_t commands_len = sizeof(COMMANDS) / sizeof(COMMANDS[0]);
    if (ArgParser(argc, argv, &flags, (const option_t**) &COMMANDS, commands_len) == INPUT_ERROR) {
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

    FILE* input_file = fopen(flags.input_file_name, "r");
    if (input_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN INPUT FILE\n" STRERROR(errno));
        return EXIT_FAILURE;
    }

    FILE* output_file = fopen(flags.output_file_name, "w");
    if (output_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN OUTPUT FILE\n" STRERROR(errno));
        return EXIT_FAILURE;
    }

    text_t text = {};
    text.sort_state = DEFAULT;

    if (StringCtor(&text, input_file) != NO_ERRORS) {
        return EXIT_FAILURE;
    }

    bool empty_file_flag = false;
    if (text.symbols_amount == 1 || text.strings_amount == 0) {
        printf("EMPTY FILE\n");
        empty_file_flag = true;
    }

    if (!empty_file_flag) {
        SortIncludes(&text);
        PrintSortedIncludes(&text, output_file);
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
