#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "sort.h"
#include "defines.h"

void BubbleSort(void* base, const size_t nel, const size_t width, compare_t compar) {
    for (size_t i = 0; i < nel; i++) {
        for (size_t j = i + 1; j < nel; j++) {
            if (compar(((char*) base + i * width), ((char*) base + j * width)) > 0) {
                SwapElements(((char*) base + i * width), ((char*) base + j * width), width);
            }
        }
    }
}

void QuickSort(void* base, const size_t nel, const size_t width, compare_t compar) {
    QuickSortBasic(base, width, 0, nel - 1, compar);
}
//ANCHOR - static
void QuickSortBasic(void* base_void, const size_t width, const size_t left, const size_t right, compare_t compar){
    assert(base_void != nullptr);

    if (left >= right) {
        return;
    }

    char* base = (char*) base_void;

    SwapElements((base + left * width), (base + ((left + right) / 2) * width), width);

    size_t last = left;

    for(size_t i = left + 1; i <= right; i++) {
        if (compar((base + left * width), (base + i * width)) > 0) {
            SwapElements((base + (++last) * width), (base + i * width), width);
        }
    }

    SwapElements((base + left * width), (base + last * width), width);

    QuickSortBasic(base, width, left, last, compar);
    QuickSortBasic(base, width, last + 1, right, compar);
}

void SortText(void* base, size_t nel, size_t width, compare_t compar, sort_type_t sort_type) {
    switch (sort_type) {
        case QUICK:
            QuickSort(base, nel, width, compar);
            break;
        case BUBBLE:
            BubbleSort(base, nel, width, compar);
            break;
        default:
            break;
    }
}

void SwapElements(void* s1, void* s2, const size_t width) {
    size_t i = 0;

    size_t n = width / sizeof(uint64_t);

    uint64_t s = 0;
    for (; i < n; i++) {
        memcpy(&s, (uint64_t*) s1 + i, sizeof(uint64_t));
        memcpy((uint64_t*) s1 + i, (uint64_t*) s2 + i, sizeof(uint64_t));
        memcpy((uint64_t*) s2 + i, &s, sizeof(uint64_t));
    }
//NOTE - move pointers, not i *= 2
    i *= 2;
    if (width & 0x04) {
        memcpy(&s, (uint32_t*) s1 + i, sizeof(uint32_t));
        memcpy((uint32_t*) s1 + i, (uint32_t*) s2 + i, sizeof(uint32_t));
        memcpy((uint32_t*) s2 + i, &s, sizeof(uint32_t));
        i++;
    }

    i *= 2;
    if (width & 0x02) {
        memcpy(&s, (uint16_t*) s1 + i, sizeof(uint16_t));
        memcpy((uint16_t*) s1 + i, (uint16_t*) s2 + i, sizeof(uint16_t));
        memcpy((uint16_t*) s2 + i, &s, sizeof(uint16_t));
        i++;
    }

    i *= 2;
    if (width & 0x01) {
        memcpy(&s, (uint8_t*) s1 + i, sizeof(uint8_t));
        memcpy((uint8_t*) s1 + i, (uint8_t*) s2 + i, sizeof(uint8_t));
        memcpy((uint8_t*) s2 + i, &s, sizeof(uint8_t));
    }
}
