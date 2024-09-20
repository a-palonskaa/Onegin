#ifndef PARSE_ARGUMENTS_H
#define PARSE_ARGUMENTS_H

#include <stdio.h>

#include "define_constants.h"

typedef enum {
    BUBBLE_SORT = 0,
    QUICK_SORT  = 1
} sort_type_t;

typedef enum {
    FORWARD  = 0,
    BACKWARD = 1,
    NO_SORT  = 2
} sort_mode_t;

typedef enum {
    NO_CMD_ERRORS = 0,
    INPUT_ERROR   = 1
} cmd_error_t;

const size_t MAX_SORT_AMOUNT = 10;
const size_t DEFAULT_SORT_AMOUNT = 3;

typedef struct {
    const char* input_file_name;
    const char* output_file_name;

    sort_type_t sort_type;
    sort_mode_t sort_mode[MAX_SORT_AMOUNT];
    sort_mode_t sort_mode_default[DEFAULT_SORT_AMOUNT];

    int sort_mode_valid;
    int input_valid;
    int output_valid;

    size_t sort_mode_cnt;
    size_t sort_mode_cnt_default;
} flags_t;

typedef enum {
    DEFAULT = 0,
    COMPLEX = 1
} sort_state_t;

typedef cmd_error_t (*changeflag_t) (flags_t* flags, const char* argv);

typedef struct{
    const char* name;
    const char* long_name;
    changeflag_t change;
    const char* description;
    bool has_arg;
} option_t;

cmd_error_t ArgParser(int argc, const char* argv[], flags_t* flags);
void InitiallizeFlags(flags_t* flags);

#endif /* PARSE_ARGUMENTS_H */
