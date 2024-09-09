#include "sort.h"
#include "string_functions.h"

void StrBubbleSort(strdata_t* text_strdata, cmpr_mode_t CompareStr) {
    for (size_t i = 0; i < STR_CNT; i++) {
        for (size_t j = i + 1; j < STR_CNT; j++) {
            if (CompareStr(i, j, text_strdata)) {
                SwapStr(i, j, text_strdata);
            }
        }
    }
}

void StrQuickSort(strdata_t* text_strdata, size_t left, size_t right, cmpr_mode_t CompareStr){
    if (left >= right) {
        return;
    }

    SwapStr(left, (left + right) / 2, text_strdata);

    size_t last = left;

    for(size_t i = left + 1; i <= right; i++) {
        if (!CompareStr(i, left, text_strdata)) {
            SwapStr(++last, i, text_strdata);
        }
    }

    SwapStr(left, last, text_strdata);

    StrQuickSort(text_strdata, left, last, CompareStr);
    StrQuickSort(text_strdata, last + 1, right, CompareStr);
}
