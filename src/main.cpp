#include <stdio.h>

#include "test_program.h"
#include "sort.h"

int main() {
    FILE* input_file = fopen("./txtfiles/onegin.txt", "r");

    char text[STR_CNT][MAX_STR_LEN] = {};
    char* index[STR_CNT] = {};

    for (int i = 0; i < STR_CNT; i++) {
        index[i] = &text[i][0];
        int c;
        int j = 0;
        while(j < MAX_STR_LEN && (c = fgetc(input_file)) != '\n' && c != EOF) {
            text[i][j++] = (char) c;
        }
        //fgets(&text[i][0],MAX_STR_LEN, input_file);
    }

    StrBubbleSort(index);

    PrintTextTestMode(index);

    fclose(input_file);
}

