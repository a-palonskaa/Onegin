#ifndef SORT_H
#define SORT_H

#include <stdio.h>

#include "define_constants.h"

typedef int (*compare_t)(const void *, const void *);

void BubbleSort(void* base, size_t nel, size_t width, compare_t compar);
void QuickSort(void* base, size_t nel, size_t width, compare_t compar);
void QuickSortBasic(void* base, size_t width, size_t left, size_t right, compare_t compar);
void SortText(void* base, size_t nel, size_t width, compare_t compar, sort_type_t sort_type);
void SwapElements(void* s1, void* s2, size_t width);

#endif /* SORT_H */

