#include "test_program.h"

void PrintTextTestMode(str_data_t* str_data) {
    for (size_t i = 0; i < str_data->str_cnt; i++) { //ХУЙНЯ ПЕРЕДЕЛЫВАЙ -   14
        for (size_t j = 0; j < str_data->str_store_data[i].str_len - 1; j++) {
            printf("%c", str_data->str_store_data[i].str_begin[j]);
        }

        printf("\n");
    }
}

void PrintSymbolsTestMode(str_data_t* str_data) {
    for (size_t i = 0; i < str_data->str_cnt; i++) { //ХУЙНЯ ПЕРЕДЕЛЫВАЙ -   14
        for (size_t j = 0; j < str_data->str_store_data[i].str_len - 1; j++) {
            printf("text[%zu][%zu] = %c (%d) ", i, j,
                   str_data->str_store_data[i].str_begin[j],
                   str_data->str_store_data[i].str_begin[j]);
        }

        printf("\n");
    }
}
