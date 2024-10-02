#ifndef HSORT_ARGPARSER_H
#define HSORT_ARGPARSER_H

#include "parse_arguments.h"

const option_t COMMANDS[] = {
    // short_name  long_name         changeflag function         description                     has_arg
        {"-i",  "--input_file",    &ChangeFlagInputFile,      "Read data from the file"          , true},
        {"-o",  "--output_file",   &ChangeFlagOutputFile,     "Print results in the file "       , true},
        {"-h",  "--help",          &Help,                     "Help"                             , false},
        {"-l",  "--logger_output", &ChangeFlagLoggerOutput,   "Print logger messages in the file", true},
};

cmd_error_t ChangeFlagInputFile(flags_t* flags, const char* arg);
cmd_error_t ChangeFlagOutputFile(flags_t* flags, const char* arg);
cmd_error_t ChangeFlagLoggerOutput(flags_t* flags, const char* arg);
cmd_error_t Help(flags_t* flags, const char* arg);

void InitiallizeFlagsOnegin(flags_t* flags);

#endif /* HSORT_ARGPARSER_H */
