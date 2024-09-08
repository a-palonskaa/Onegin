#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "test_program.h"
#include "sort.h"

size_t GetTextSymbolAmount(FILE* input_file);

int main() {
    FILE* input_file = fopen("./txtfiles/onegin.txt", "r");
    const size_t SYMBOL_AMOUNT = GetTextSymbolAmount(input_file);
    printf("SYMBOL_AMOUNT = %zu", SYMBOL_AMOUNT);
    strdata_t text_strdata[STR_CNT] = {};
    char* text = (char*) calloc(SYMBOL_AMOUNT, sizeof(char));

    for (size_t i = 0, symbol_cnt = 0; i < STR_CNT && symbol_cnt < SYMBOL_AMOUNT; i++) {
        text_strdata[i].str_begin = text + symbol_cnt;

        fgets(text_strdata[i].str_begin, MAX_STR_LEN, input_file);

        text_strdata[i].str_len = strnlen(text_strdata[i].str_begin, MAX_STR_LEN);
        text_strdata[i].str_begin[text_strdata[i].str_len - 1] = '\0';
        symbol_cnt += text_strdata[i].str_len;
    }

    StrBubbleSort(text_strdata);

    PrintTextTestMode(text_strdata);

    fclose(input_file);
}

size_t GetTextSymbolAmount(FILE* input_file) {
    struct stat file_data = {};
    fstat(fileno(input_file), &file_data); //REVIEW - нахуя off_t который long long
    return (size_t) file_data.st_size;
}
