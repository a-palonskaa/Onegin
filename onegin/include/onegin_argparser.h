#ifndef ONEGIN_ARGPARSER_H
#define ONEGIN_ARGPARSER_H

#include "parse_arguments.h"
#include "define_constants.h"

typedef struct {
    const char* input_file_name;
    const char* output_file_name;
    const char* logger_output_file;

    sort_type_t sort_type;
    sort_mode_t sort_mode[MAX_SORT_AMOUNT];
    sort_mode_t sort_mode_default[DEFAULT_SORT_AMOUNT];

    int sort_mode_valid;
    int input_valid;
    int output_valid;

    size_t sort_mode_cnt;
    size_t sort_mode_cnt_default;
} flags_t;

//----------------------------------------------------------------------------------------------

void InitiallizeFlagsOnegin(void* flag);

cmd_error_t ChangeFlagInputFile(void* flag, const char* arg);
cmd_error_t ChangeFlagOutputFile(void* flag, const char* arg);
cmd_error_t ChangeFlagLoggerOutput(void* flag, const char* arg);

cmd_error_t ChangeFlagModeBubbleSort(void* flag, const char* arg);
cmd_error_t ChangeFlagModeQuickSort(void* flag, const char* arg);

cmd_error_t ChangeFlagForwardSort(void* flag, const char* arg);
cmd_error_t ChangeFlagBackwardSort(void* flag, const char* arg);
cmd_error_t ChangeFlagNoSort(void* flag, const char* arg);

cmd_error_t Help(void* flag, const char* arg);

cmd_error_t ValidateInput(const void* flag);

//----------------------------------------------------------------------------------------------

const option_t COMMANDS[] = {
    // short_name     long_name       changeflag function         description                      has_arg
        {"-bs",  "--bubble_sort",   &ChangeFlagModeBubbleSort, "Testing mode"                     , false},
        {"-qs",  "--quick_sort",    &ChangeFlagModeQuickSort,  "Solving mode"                     , false},
        {"-i",   "--input_file",    &ChangeFlagInputFile,      "Read data from the file"          , true},
        {"-o",   "--output_file",   &ChangeFlagOutputFile,     "Print results in the file "       , true},
        {"-h",   "--help",          &Help,                     "Help"                             , false},
        {"-b",   "--backward_sort", &ChangeFlagBackwardSort,   "Sort from the end"                , false},
        {"-f",   "--forward_sort",  &ChangeFlagForwardSort,    "Sort from the begin"              , false},
        {"-n",   "--no_sort",       &ChangeFlagNoSort,         "No sort"                          , false},
        {"-l",   "--logger_output", &ChangeFlagLoggerOutput,   "Print logger messages in the file", true},
};

const size_t CMD_ARRAY_LENGTH = sizeof(COMMANDS) / sizeof(COMMANDS[0]);

#endif /* ONEGIN_ARGPARSER_H */
