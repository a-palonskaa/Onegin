#include "sort.h"
#include "string_functions.h"

void StrBubbleSort(text_t* text, cmpr_mode_t сompare_str) {
    for (size_t i = 0; i < text->strings_amount; i++) {
        for (size_t j = i + 1; j < text->strings_amount; j++) {
            if (сompare_str(i, j, text->strings)) {
                SwapStrings(i, j, text->strings);
            }
        }
    }
}

void StrQuickSort(text_t* text, size_t left, size_t right, cmpr_mode_t сompare_str){
    if (left >= right) {
        return;
    }

    SwapStrings(left, (left + right) / 2, text->strings);

    size_t last = left;

    for(size_t i = left + 1; i <= right; i++) {
        if (!сompare_str(i, left, text->strings)) {
            SwapStrings(++last, i, text->strings);
        }
    }

    SwapStrings(left, last, text->strings);

    StrQuickSort(text, left, last, сompare_str);
    StrQuickSort(text, last + 1, right, сompare_str);
}
