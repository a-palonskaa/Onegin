#include <stdio.h>
#include "utf8_decode.h"
#include "defines.h"
#include "utf8_text.h"
#include "print.h"
#include "logger.h"
#include "string_functions.h"
#include "sort.h"
#include <time.h>

int main() {
    FILE* logger_output = fopen("utf8/logger.txt", "w");

    if (logger_output== nullptr) {
        perror("FAILED TO OPEN LOGGER OUTPUT FILE");
        logger_output = stderr;
    }

    LoggerSetLevel(DEBUG);
    LoggerSetFile(logger_output);

    FILE* input_file  = fopen("utf8/in.txt", "r");
    if (input_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN INPUT FILE\n" STRERROR(errno));
        return EXIT_FAILURE;
    }

    FILE* output_file = fopen("utf8/out.txt", "w");
    if (output_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN OUTPUT FILE\n" STRERROR(errno));
        return EXIT_FAILURE;
    }

    text_t text = {};

    StringCtor(&text, input_file);

    const size_t str_cnt = text.strings_amount;
    const size_t strint_t_size = sizeof(string_t);

    fprintf(output_file, "Forward:\n");
    SortText(text.strings, str_cnt, strint_t_size, CompareStringsForward, QUICK_SORT);
    PrintText(&text, output_file);

    fprintf(output_file, "\nBackward:\n");
    SortText(text.strings, str_cnt, strint_t_size, CompareStringsBackward, QUICK_SORT);
    PrintText(&text, output_file);

    StringDtor(&text);
}
