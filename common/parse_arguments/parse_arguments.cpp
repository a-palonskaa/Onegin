#include <assert.h>
#include <string.h>

#include "parse_arguments.h"

static cmd_error_t ChangeFlagInputFile(flags_t* flags, const char* arg);
static cmd_error_t ChangeFlagOutputFile(flags_t* flags, const char* arg);

static cmd_error_t ChangeFlagModeBubbleSort(flags_t* flags, const char* arg);
static cmd_error_t ChangeFlagModeQuickSort(flags_t* flags, const char* arg);

static cmd_error_t ChangeFlagForwardSort(flags_t* flags, const char* arg);
static cmd_error_t ChangeFlagBackwardSort(flags_t* flags, const char* arg);
static cmd_error_t ChangeFlagNoSort(flags_t* flags, const char* arg);

static cmd_error_t Help(flags_t* flags, const char* arg);
static cmd_error_t ValidateInput(const flags_t* flags);
static void PrintHelp();

const char* ONEGIN_ORIGINAL = "./txtfiles/sorted_onegin_full.txt";
const char* ONEGIN_SORTED = "./txtfiles/onegin_full.txt";

const option_t COMMANDS[] = {
    //   short_name      long_name         changeflag function         description               has_arg
        {"-bs",       "--bubble_sort",   &ChangeFlagModeBubbleSort, "Testing mode"              , false},
        {"-qs",       "--quick_sort",    &ChangeFlagModeQuickSort,  "Solving mode"              , false},
        {"-i",        "--input_file",    &ChangeFlagInputFile,      "Read data from the file"   , true},
        {"-o",        "--output_file",   &ChangeFlagOutputFile,     "Print results in the file ", true},
        {"-h",        "--help",          &Help,                     "Help"                      , false},
        {"-b",        "--backward_sort", &ChangeFlagBackwardSort,   "Sort from the end"         , false},
        {"-f",        "--forward_sort",  &ChangeFlagForwardSort,    "Sort from the begin"       , false},
        {"-n",        "--no_sort",       &ChangeFlagNoSort,         "No sort"                   , false}
};

const size_t COMMANDS_ARRAY_LENGTH = sizeof(COMMANDS) / sizeof(COMMANDS[0]);

cmd_error_t ArgParser(int argc, const char* argv[], flags_t* flags) {
    assert(argv  != nullptr);
    assert(flags != nullptr);
    assert(argc >= 0);

    if (argc == 0) {
        return INPUT_ERROR;
    }

    while (--argc > 0) {
        argv++;
        int has_arg_validate = 0;

        for (size_t i = 0; i < COMMANDS_ARRAY_LENGTH; i++) {
            if(!(strcmp(*argv, COMMANDS[i].name) &&
                 strcmp(*argv, COMMANDS[i].long_name))) {

                has_arg_validate++;

                if (COMMANDS[i].has_arg && argc <= 1) {
                    PrintHelp();
                    return INPUT_ERROR;
                }

                cmd_error_t state = NO_CMD_ERRORS;

                if (!COMMANDS[i].has_arg) {
                    state = COMMANDS[i].change(flags, nullptr);
                }
                else {
                    argc--;
                    state = COMMANDS[i].change(flags, *++argv);
                }

                if (state == INPUT_ERROR) {
                    printf("ERROR OF COMMAND\n");
                    return INPUT_ERROR;
                }
            }
        }
        if (!has_arg_validate) {
            printf("UNKNOWN COMMAND\n");
            return INPUT_ERROR;
        }
    }
    return ValidateInput(flags);
}

cmd_error_t ChangeFlagInputFile(flags_t* flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->input_valid++;
    flags->input_file_name = arg;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagOutputFile(flags_t* flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->output_valid++;
    flags->output_file_name = arg;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagModeBubbleSort(flags_t* flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->sort_mode_valid++;
    flags->sort_type = BUBBLE_SORT;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagModeQuickSort(flags_t* flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->sort_mode_valid++;
    flags->sort_type = QUICK_SORT;

    return NO_CMD_ERRORS;
}

cmd_error_t Help(flags_t* flags, const char* arg) {
    (void) arg;
    (void) flags;

    PrintHelp();
    return INPUT_ERROR;
}

void PrintHelp() {
    for (size_t i = 0; i < COMMANDS_ARRAY_LENGTH; i++) {
        printf("%10s %10s %-10s" "\n", COMMANDS[i].name,
                                       COMMANDS[i].long_name,
                                       COMMANDS[i].description);
    }
}

cmd_error_t ValidateInput(const flags_t* flags) {
    assert(flags != nullptr);

    if (flags->output_valid > 1 ||
        flags->input_valid > 1  ||
        flags->sort_mode_valid > 1) {
        printf("MUTUAL DESTRUCTION ERROR\n");
        return INPUT_ERROR;
    }
    return NO_CMD_ERRORS;
}

void InitiallizeFlags(flags_t* flags) {
    assert(flags != nullptr);

    flags->sort_type = QUICK_SORT;

    flags->output_file_name = ONEGIN_ORIGINAL;
    flags->input_file_name = ONEGIN_SORTED;

    flags->sort_mode_cnt_default = DEFAULT_SORT_AMOUNT;

    STATIC_ASSERT(DEFAULT_SORT_AMOUNT == 3, Default_sorts_amount_should_be_3);
    flags->sort_mode_default[0] = FORWARD;
    flags->sort_mode_default[1] = BACKWARD;
    flags->sort_mode_default[2] = NO_SORT;

    for (size_t i = 0; i < MAX_SORT_AMOUNT; i++) {
        flags->sort_mode[i] = NO_SORT;
    }

    flags->sort_mode_valid = 0;
    flags->output_valid    = 0;
    flags->input_valid     = 0;
    flags->sort_mode_cnt   = 0;
}

cmd_error_t ChangeFlagBackwardSort(flags_t* flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    if (flags->sort_mode_cnt >= MAX_SORT_AMOUNT) {
        return INPUT_ERROR;
    }

    flags->sort_mode[flags->sort_mode_cnt++] = BACKWARD;
    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagForwardSort(flags_t* flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    if (flags->sort_mode_cnt >= MAX_SORT_AMOUNT) {
        return INPUT_ERROR;
    }

    flags->sort_mode[flags->sort_mode_cnt++] = FORWARD;
    return NO_CMD_ERRORS;
}

static cmd_error_t ChangeFlagNoSort(flags_t* flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    if (flags->sort_mode_cnt >= MAX_SORT_AMOUNT) {
        return INPUT_ERROR;
    }

    flags->sort_mode[flags->sort_mode_cnt++] = NO_SORT;
    return NO_CMD_ERRORS;
}
