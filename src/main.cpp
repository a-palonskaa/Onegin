#include <stdio.h>
#include <stdlib.h>

#include "test_program.h"
#include "sort.h"


int main() {
    FILE* input_file = fopen("./txtfiles/onegin.txt", "r");

    //char text[STR_CNT][MAX_STR_LEN] = {};
    strdata_t text_strdata[STR_CNT] = {};
    char* text = (char*) calloc(SYMBOL_AMOUNT, sizeof(char));

    for (size_t i = 0, symbol_cnt = 0; i < STR_CNT; i++) {
        int c = 0;
        size_t j = 0;

        text_strdata[i].str_begin = text + symbol_cnt;

        while(j++ < MAX_STR_LEN - 1 && (c = fgetc(input_file)) != '\n' && c != EOF) {
            text[symbol_cnt] = (char) c;
            symbol_cnt++;
        }
        text[symbol_cnt] = '\0';
        symbol_cnt++;

        text_strdata[i].str_len = j;
        //fgets(&text[i][0], MAX_STR_LEN, input_file);
    }
    StrBubbleSort(text_strdata);

    PrintTextTestMode(text_strdata);

    fclose(input_file);
}

