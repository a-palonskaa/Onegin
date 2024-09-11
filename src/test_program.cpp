#include "test_program.h"

void PrintTextTestMode(text_t* text) {
    for (size_t i = 0; i < text->strings_amount; i++) {
        for (size_t j = 0; j < text->strings[i].length - 1; j++) {
            printf("%c", text->strings[i].begin[j]);
        }

        printf("\n");
    }
}

void PrintSymbolsTestMode(text_t* text) {
    for (size_t i = 0; i < text->strings_amount; i++) {
        for (size_t j = 0; j < text->strings[i].length - 1; j++) {
            printf("text[%zu][%zu] = %c (%d) ", i, j,
                   text->strings[i].begin[j],
                   text->strings[i].begin[j]);
        }

        printf("\n");
    }
}

