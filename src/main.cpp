#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_program.h"
#include "sort.h"
#include "text_inf_lib.h"
#include "string_functions.h"

int main() {
    FILE* input_file = fopen("./txtfiles/onegin.txt", "r");

    if (input_file == nullptr) {
        perror("FAILED TO OPEN OUTPUT FILE\n");
        return EXIT_FAILURE;
    }

    const size_t SYMBOL_AMOUNT = CountTextSymbols(input_file);
    const size_t STR_CNT       = CountTextLines(input_file);

    str_store_data_t* str_store_data = (str_store_data_t*) calloc(STR_CNT, sizeof(str_store_data_t));
    char* text                       = (char*) calloc(SYMBOL_AMOUNT, sizeof(char));

    cmpr_mode_t CompareStr = &CompareStrLast;
    str_data_t  str_data = {str_store_data, STR_CNT};

    for (size_t i = 0, symbol_cnt = 0; i < STR_CNT && symbol_cnt < SYMBOL_AMOUNT; i++) {
        str_store_data[i].str_begin = text + symbol_cnt;

        fgets(str_store_data[i].str_begin, MAX_STR_LEN, input_file);

        str_store_data[i].str_len = strnlen(str_store_data[i].str_begin, MAX_STR_LEN);
        str_store_data[i].str_begin[str_store_data[i].str_len - 1] = '\0';

        symbol_cnt += str_store_data[i].str_len;
    }

   // StrQuickSort(str_store_data, 0, STR_CNT - 1, CompareStr);
    StrQuickSort(&str_data, 0, STR_CNT - 1, CompareStr);

    //PrintTextTestMode(str_store_data, STR_CNT);
    PrintTextTestMode(&str_data);

    free(str_store_data);
    str_store_data = nullptr;
    free(text);
    text = nullptr;

    if(fclose(input_file) == EOF) {
        perror("FAILED TO CLOSE OUTPUT FILE\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
