#include <stdio.h>

#include "test_program.h"
#include "string_functions.h"

int main() {
    FILE* input_file = fopen("onegin.txt", "r");

    char text[STR_CNT][MAX_STR_LEN] = {};

    for (int i = 0; i < STR_CNT; i++) {
        int c;
        int j = 0;
        while(j < MAX_STR_LEN && (c = fgetc(input_file)) != '\n' && c != EOF) {
            text[i][j++] = (char) c;
        }
        //fgets(&text[i][0],MAX_STR_LEN, input_file);
    }

    for (int i = 0; i < STR_CNT; i++) {
        for (int j = i + 1; j < STR_CNT; j++) {
            if (CompareStr(text[i], text[j])) {
                SwapStr(text[i], text[j]);
            }
        }
    }

    PrintTextTestMode(text);

    fclose(input_file);
}

