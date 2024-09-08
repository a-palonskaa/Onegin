#include "test_program.h"

void PrintTextTestMode(strdata_t* text_strdata) {
    for (size_t i = 0; i < STR_CNT; i++) {
        for (size_t j = 0; j < text_strdata[i].str_len; j++) {
            printf("%c", text_strdata[i].str_begin[j]);
        }

        printf("\n");
    }
}

void PrintSymbolsTestMode(const char text[][MAX_STR_LEN]) {
    for (size_t i = 0; i < STR_CNT; i++) {
        for (size_t j = 0; j < MAX_STR_LEN; j++) {
            printf("text[%zu][%zu] = %c (%d) ", i, j, text[i][j], text[i][j]);
        }

        printf("\n");
    }
}
