#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_program.h"
#include "sort.h"
#include "text_t_lib.h"
#include "string_functions.h"
// TODO: добавить флаги для файлов argv argc (если сильно хочется прибивать пути, то через константы)
int main() {
    const char* ONEGIN = "./txtfiles/onegin.txt";

    FILE* input_file = fopen(ONEGIN, "r");

    if (input_file == nullptr) {
        perror("FAILED TO OPEN OUTPUT FILE\n");
        return EXIT_FAILURE;
    }

    text_t text = {};

    StringCtor(&text, input_file);

    StrQuickSort(text.strings, text.strings_amount, sizeof(string_t), CompareStringsBackward);
    //StringBubbleSort(text.strings, text.strings_amount, sizeof(string_t), CompareStringsBackward);
    PrintTextTestMode(&text);

    StringDtor(&text);

    if(fclose(input_file) == EOF) {
        perror("FAILED TO CLOSE OUTPUT FILE\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

//merge sort
