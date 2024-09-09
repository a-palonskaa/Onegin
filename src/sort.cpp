#include "sort.h"
#include "string_functions.h"

void StrBubbleSort(str_data_t* str_data, cmpr_mode_t CompareStr) {
    for (size_t i = 0; i < str_data->str_cnt; i++) {
        for (size_t j = i + 1; j < str_data->str_cnt; j++) {
            if (CompareStr(i, j, str_data->str_store_data)) {
                SwapStr(i, j, str_data->str_store_data);
            }
        }
    }
}

void StrQuickSort(str_data_t* str_data, size_t left, size_t right, cmpr_mode_t CompareStr){
    if (left >= right) {
        return;
    }

    SwapStr(left, (left + right) / 2, str_data->str_store_data);

    size_t last = left;

    for(size_t i = left + 1; i <= right; i++) {
        if (!CompareStr(i, left, str_data->str_store_data)) {
            SwapStr(++last, i, str_data->str_store_data);
        }
    }

    SwapStr(left, last, str_data->str_store_data);

    StrQuickSort(str_data, left, last, CompareStr);
    StrQuickSort(str_data, last + 1, right, CompareStr);
}
