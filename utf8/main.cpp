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
    FILE* logger_output = fopen("logger.txt", "w");

    if (logger_output== nullptr) {
        perror("FAILED TO OPEN LOGGER OUTPUT FILE");
        logger_output = stderr;
    }

    LoggerSetLevel(DEBUG);
    LoggerSetFile(logger_output);

    FILE* input_file  = fopen("in.txt", "r");
    if (input_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN INPUT FILE\n" STRERROR(errno));
        return EXIT_FAILURE;
    }

    FILE* output_file = fopen("out.txt", "w");
    if (output_file == nullptr) {
        Log(ERROR, "FAILED TO OPEN OUTPUT FILE\n" STRERROR(errno));
        return EXIT_FAILURE;
    }

    text_t text = {};

    StringCtor(&text, input_file);

    printf("amount of the strings is %zu\n", text.strings_amount);
    printf("amount of the symbols is %zu\n", text.symbols_amount);

    const size_t str_cnt = text.strings_amount;
    const size_t strint_t_size = sizeof(string_t);
clock_t time1 = clock();
    fprintf(output_file, "Forward:\n");
    SortText(text.strings, str_cnt, strint_t_size, CompareStringsForward, QUICK);
    PrintText(&text, output_file);

    fprintf(output_file, "\nBackward:\n");
    SortText(text.strings, str_cnt, strint_t_size, CompareStringsForward, QUICK);
    PrintText(&text, output_file);
    clock_t time2 = clock();
printf("Working time is = %ld\n", time2 - time1);
    StringDtor(&text);
}
