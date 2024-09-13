#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_results.h"
#include "sort.h"
#include "text_t_lib.h"
#include "string_functions.h"
// TODO: добавить флаги для файлов argv argc (если сильно хочется прибивать пути, то через константы)
int main() {
    const char* ONEGIN = "./txtfiles/onegin_full.txt";
    const char* SORTED_ONEGIN = "./txtfiles/sorted_onegin_full.txt";

    FILE* input_file  = fopen(ONEGIN, "r");

    if (input_file == nullptr) {
        perror("FAILED TO OPEN INPUT FILE\n");
        return EXIT_FAILURE;
    }

    FILE* output_file = fopen(SORTED_ONEGIN, "w");

    if (output_file == nullptr) {
        perror("FAILED TO OPEN OUTPUT FILE\n");
        return EXIT_FAILURE;
    }

    text_t text = {};

    StringCtor(&text, input_file);

    QuickSort(text.backward_sorted_strings, text.strings_amount, sizeof(string_t), CompareStringsBackward);
    QuickSort(text.forward_sorted_strings, text.strings_amount, sizeof(string_t), CompareStringsForward);

    PrintSortedText(output_file, &text);

    StringDtor(&text);

    if(fclose(input_file) == EOF) {
        perror("FAILED TO CLOSE INPUT FILE\n");
        return EXIT_FAILURE;
    }

    if(fclose(output_file) == EOF) {
        perror("FAILED TO CLOSE OUTPUT FILE\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

//merge sort
