#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_program.h"
#include "sort.h"
#include "text_inf_lib.h"
#include "string_functions.h"

int main() {
    FILE* input_file = fopen("./txtfiles/onegin.txt", "r");

    const size_t SYMBOL_AMOUNT = GetTextSymbolAmount(input_file);
    strdata_t text_strdata[STR_CNT] = {};
    char* text = (char*) calloc(SYMBOL_AMOUNT, sizeof(char));
    cmpr_mode_t CompareStr = &CompareStrLast;

    for (size_t i = 0, symbol_cnt = 0; i < STR_CNT && symbol_cnt < SYMBOL_AMOUNT; i++) {
        text_strdata[i].str_begin = text + symbol_cnt;

        fgets(text_strdata[i].str_begin, MAX_STR_LEN, input_file);

        text_strdata[i].str_len = strnlen(text_strdata[i].str_begin, MAX_STR_LEN);
        text_strdata[i].str_begin[text_strdata[i].str_len - 1] = '\0';

        symbol_cnt += text_strdata[i].str_len;
    }

    StrQuickSort(text_strdata, 0, STR_CNT - 1, CompareStr);

    PrintTextTestMode(text_strdata);

    fclose(input_file);
}
