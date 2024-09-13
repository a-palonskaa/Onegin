#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <stdio.h>

typedef enum {
    NO_CMD_ERRORS       = 0,   ///< no errors
    NO_INPUT_ERRORS     = 1,   ///< no input errors
    INPUT_ERROR         = 2,   ///< input error
    ROOTS_NUMBER_ERROR  = 3,   ///< error number of roots
    END_OF_FILE         = 4,   ///< end of file
    SYMBOLS_INPUT_ERROR = 5    ///< error of detecting non-number, non-spaces symbols
} cmd_error_t;

typedef enum {
    BUBBLE_SORT = 0,
    QUICK_SORT  = 1
} sort_type_t;

typedef struct {
    const char* input_file_name;
    const char* output_file_name;
    sort_type_t sort_mode;

    int sort_mode_valid;
    int input_valid;
    int output_valid;
} flags_t;

typedef cmd_error_t (*changeflag_t) (flags_t *flags, const char *argv);

typedef struct{
    const char *name;
    const char *long_name;
    changeflag_t change;
    const char *description;
    bool has_arg;
} option_t;


cmd_error_t ArgParser(int argc, const char *argv[], flags_t *flags);
void InitiallizeFlags(flags_t *flags);

#endif /* ARG_PARSER_H */
