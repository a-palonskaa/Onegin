#include "sort.h"
#include "string_functions.h"

void StrBubbleSort(strdata_t* text_strdata) {
    for (size_t i = 0; i < STR_CNT; i++) {
        for (size_t j = i + 1; j < STR_CNT; j++) {
            if (CompareStr(i, j, text_strdata)) {
                SwapStr(i, j, text_strdata);
            }
        }
    }
}
