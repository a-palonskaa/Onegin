#include <assert.h>
#include "onegin_argparser.h"

const char* ONEGIN_SORTED = "output/onegin/sorted_onegin_full.txt";
const char* ONEGIN_ORIGINAL = "txtfiles/onegin_full.txt";
const char* ONEGIN_LOGGER_OUTPUT = "output/onegin/info";

static void InitiallizeValidationFlags(void* flags);

cmd_error_t ChangeFlagInputFile(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    flags->input_valid++;
    flags->input_file_name = arg;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagLoggerOutput(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    flags->logger_output_file = arg;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagOutputFile(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    flags->output_valid++;
    flags->output_file_name = arg;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagModeBubbleSort(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    flags->sort_mode_valid++;
    flags->sort_type = BUBBLE_SORT;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagModeQuickSort(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    flags->sort_mode_valid++;
    flags->sort_type = QUICK_SORT;

    return NO_CMD_ERRORS;
}

cmd_error_t Help(void* flag, const char* arg) {
    (void) arg;
    (void) flag;

    PrintHelp();
    return INPUT_ERROR;
}

void PrintHelp() {
    for (size_t i = 0; i < CMD_ARRAY_LENGTH; i++) {
        printf("%10s %10s %-10s" "\n", COMMANDS[i].name,
                                       COMMANDS[i].long_name,
                                       COMMANDS[i].description);
    }
}

cmd_error_t ValidateInput(const void* flag) {
    assert(flag != nullptr);
    const flags_t* flags = (const flags_t*) flag;

    if (flags->output_valid > 1 ||
        flags->input_valid > 1  ||
        flags->sort_mode_valid > 1) {
        printf("MUTUAL DESTRUCTION ERROR\n");
        return INPUT_ERROR;
    }
    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagBackwardSort(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    if (flags->sort_mode_cnt >= MAX_SORT_AMOUNT) {
        return INPUT_ERROR;
    }

    flags->sort_mode[flags->sort_mode_cnt++] = BACKWARD;
    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagForwardSort(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    if (flags->sort_mode_cnt >= MAX_SORT_AMOUNT) {
        return INPUT_ERROR;
    }

    flags->sort_mode[flags->sort_mode_cnt++] = FORWARD;
    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagNoSort(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    if (flags->sort_mode_cnt >= MAX_SORT_AMOUNT) {
        return INPUT_ERROR;
    }

    flags->sort_mode[flags->sort_mode_cnt++] = NO_SORT;
    return NO_CMD_ERRORS;
}


void InitiallizeFlagsOnegin(void* flag) {
    assert(flag != nullptr);
    flags_t* flags = (flags_t*) flag;

    flags->sort_type = QUICK_SORT;

    flags->output_file_name   = ONEGIN_SORTED;
    flags->input_file_name    = ONEGIN_ORIGINAL;
    flags->logger_output_file = ONEGIN_LOGGER_OUTPUT;

    STATIC_ASSERT(DEFAULT_SORT_AMOUNT == 3, Default_sorts_amount_should_be_3);
    flags->sort_mode_cnt_default = DEFAULT_SORT_AMOUNT;

    flags->sort_mode_default[0] = FORWARD;
    flags->sort_mode_default[1] = BACKWARD;
    flags->sort_mode_default[2] = NO_SORT;

    for (size_t i = 0; i < MAX_SORT_AMOUNT; i++) {
        flags->sort_mode[i] = NO_SORT;
    }

    InitiallizeValidationFlags(flags);
}

static void InitiallizeValidationFlags(void* flag) {
    flags_t* flags = (flags_t*) flag;

    flags->sort_mode_valid = 0;
    flags->output_valid    = 0;
    flags->input_valid     = 0;
    flags->sort_mode_cnt   = 0;
}
