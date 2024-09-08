#include "sort.h"
#include "string_functions.h"

void StrBubbleSort(char* index[]) {
    for (int i = 0; i < STR_CNT; i++) {
        for (int j = i + 1; j < STR_CNT; j++) {
            if (CompareStr(index[i], index[j])) {
                SwapStr(&index[i], &index[j]);
            }
        }
    }
}
