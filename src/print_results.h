#ifndef PRINT_RESULTS_H
#define PRINT_RESULTS_H

#include <stdio.h>

#include "text_t_lib.h"
#include "string_functions.h"

void PrintTextTestMode(FILE* output_file, text_t* text, sort_mode_t mode);
void PrintSortedText(FILE* output_file, text_t* text);

#endif /* PRINT_RESULTS_H */

