#ifndef DEFINE_CONSTANTS_H
#define DEFINE_CONSTANTS_H

#include <stdio.h>

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

#endif /* DEFINE_CONSTANTS_H */
