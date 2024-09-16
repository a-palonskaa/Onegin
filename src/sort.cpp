#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include "sort.h"
#include "string_functions.h"

void BubbleSort(void* base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
    for (size_t i = 0; i < nel; i++) {
        for (size_t j = i + 1; j < nel; j++) {
            if (compar(((char*) base + i * width), ((char*) base + j * width)) > 0) {
                SwapStrings(((char*) base + i * width), ((char*) base + j * width), width);
            }
        }
    }
}

void QuickSort(void* base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
    QuickSortBasic(base, width, 0, nel - 1, compar);
}

void QuickSortBasic(void* base_void, size_t width, size_t left, size_t right, int (*compar)(const void *, const void *)){
    assert(base_void != nullptr);

    if (left >= right) {
        return;
    }

    char* base = (char*) base_void;

    SwapStrings((base + left * width), (base + ((left + right) / 2) * width), width);

    size_t last = left;

    for(size_t i = left + 1; i <= right; i++) {
        if (compar((base + left * width), (base + i * width)) > 0) {
            SwapStrings((base + (++last) * width), (base + i * width), width);
        }
    }

    SwapStrings((base + left * width), (base + last * width), width);

    QuickSortBasic(base, width, left, last, compar);
    QuickSortBasic(base, width, last + 1, right, compar);
}
