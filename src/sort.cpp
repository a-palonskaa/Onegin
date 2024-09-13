#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include "sort.h"
#include "string_functions.h"

void StringBubbleSort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
    for (size_t i = 0; i < nel; i++) {
        for (size_t j = i + 1; j < nel; j++) {
            if (compar(((char*) base + i * width), ((char*) base + j * width)) == 1) {
                SwapStrings(((char*) base + i * width), ((char*) base + j * width), width);
            }
        }
    }
}

void QuickSort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
    QuickSortBasic(base, 0, nel - 1, compar, width);
}

void QuickSortBasic(void *base, size_t left, size_t right, int (*compar)(const void *, const void *), size_t width){
    if (left >= right) {
        return;
    }

    SwapStrings(((char*) base + left * width), ((char*) base + ((left + right) / 2) * width), width);

    size_t last = left;

    for(size_t i = left + 1; i <= right; i++) {
        if (compar(((char*) base + i * width), ((char*) base + left * width)) == -1) {
            SwapStrings(((char*) base + (++last) * width), ((char*) base + i * width), width);
        }
    }

    SwapStrings(((char*) base + left * width), ((char*) base + last * width), width);

    QuickSortBasic(base, left, last, compar, width);
    QuickSortBasic(base, last + 1, right, compar, width);
}
