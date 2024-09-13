#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include "sort.h"
#include "string_functions.h"
#include "string.h"

void StringBubbleSort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
    for (size_t i = 0; i < nel; i++) {
        for (size_t j = i + 1; j < nel; j++) {
            if (compar(((char*) base + i * width), ((char*) base + j * width)) == 1) {
                SwapStrings(((char*) base + i * width), ((char*) base + j * width), width);
            }
        }
    }
}

// void StrQuickSort(text_t* text, size_t left, size_t right, cmpr_mode_t сompare_str){
//     if (left >= right) {
//         return;
//     }
//
//     SwapStrings(left, (left + right) / 2, text->strings);
//
//     size_t last = left;
//
//     for(size_t i = left + 1; i <= right; i++) {
//         if (!сompare_str(i, left, text->strings)) {
//             SwapStrings(++last, i, text->strings);
//         }
//     }
//
//     SwapStrings(left, last, text->strings);
//
//     StrQuickSort(text, left, last, сompare_str);
//     StrQuickSort(text, last + 1, right, сompare_str);
// }
