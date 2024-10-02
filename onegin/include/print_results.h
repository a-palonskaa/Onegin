#ifndef PRINT_RESULTS_H
#define PRINT_RESULTS_H

#include <stdio.h>

#include "text_lib.h"
#include "define_constants.h"
#include "onegin_argparser.h"

void PrintTextTestMode(FILE* output_file, text_t* text, sort_mode_t mode);
void PrintSortedText(FILE* output_file, text_t* text, flags_t* flags);
void PrintNonSortedText(FILE* output_file, text_t* text);

#endif /* PRINT_RESULTS_H */

