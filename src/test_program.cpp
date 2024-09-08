#include "test_program.h"

void PrintTextTestMode(char* text[]) {
    for (int i = 0; i < STR_CNT; i++) {
        for (int j = 0; j < MAX_STR_LEN; j++) {
            printf("%c", text[i][j]);
        }

        printf("\n");
    }
}

void PrintSymbolsTestMode(const char text[][MAX_STR_LEN]) {
    for (int i = 0; i < STR_CNT; i++) {
        for (int j = 0; j < MAX_STR_LEN; j++) {
            printf("text[%d][%d] = %c (%d) ", i, j, text[i][j], text[i][j]);
        }

        printf("\n");
    }
}
