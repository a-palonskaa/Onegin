#include <stdio.h>
#include <stdlib.h>

#include "define_constants.h"
#include "includes_sort.h"
#include "sort.h"
#include "text_t_lib.h"
#include "logger.h"
// КОМПИЛЯЦИЯ: g++ ./src/includes_sort_main.cpp ./src/includes_sort.cpp ./src/sort.cpp ./src/text_t_lib.cpp ./src/logger.cpp -o cat
int main() {
    FILE* input_file  = fopen("back.cpp", "r");
    if (input_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN INPUT FILE\n", STRERROR(errno));
        return EXIT_FAILURE;
    }

    FILE* output_file = fopen("output.txt", "w");
    if (output_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN OUTPUT FILE\n", STRERROR(errno));
        return EXIT_FAILURE;
    }

    text_t text = {};
    text.sort_state = DEFAULT;

    if (StringCtor(&text, input_file) != NO_ERRORS) {
        return EXIT_FAILURE;
    }

    SortIncludes(&text, output_file);

    StringDtor(&text);

    if(fclose(input_file) == EOF) {
        Log(ERROR, "FAILED TO CLOSE INPUT FILE\n", STRERROR(errno));
        return EXIT_FAILURE;
    }

    if(fclose(output_file) == EOF) {
        Log(ERROR, "FAILED TO CLOSE OUTPUT FILE\n", STRERROR(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
