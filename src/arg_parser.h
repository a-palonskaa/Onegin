#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <stdio.h>

#include "define_constants.h"

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
