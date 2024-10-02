#include <assert.h>
#include "hsort_argparser.h"

const char* HEADER_SORT_LOGGER_OUTPUT = "output/header_sort/info";
const char* HEADER_SORT_OUTPUT = "output/header_sort/sorted_headers.txt";
const char* HEADER_SORT_INPUT = "onegin/src/main.cpp";

cmd_error_t ChangeFlagInputFile(flags_t* flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->input_valid++;
    flags->input_file_name = arg;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagLoggerOutput(flags_t* flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->logger_output_file = arg;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagOutputFile(flags_t* flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->output_valid++;
    flags->output_file_name = arg;

    return NO_CMD_ERRORS;
}

cmd_error_t Help(flags_t* flags, const char* arg) {
    (void) arg;
    (void) flags;

    PrintHelp();
    return INPUT_ERROR;
}

void InitiallizeFlagsHeaderSort(flags_t* flags) {
    assert(flags != nullptr);

    flags->sort_type = QUICK_SORT;

    flags->output_file_name   = HEADER_SORT_OUTPUT;
    flags->input_file_name    = HEADER_SORT_INPUT;
    flags->logger_output_file = HEADER_SORT_LOGGER_OUTPUT;

    InitiallizeValidationFlags(flags);
}
