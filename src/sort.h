#ifndef SORT_H
#define SORT_H

#include <stdio.h>

void BubbleSort(void* base, size_t nel, size_t width, int (*compar)(const void *, const void *));
void QuickSort(void* base, size_t nel, size_t width, int (*compar)(const void *, const void *));
void QuickSortBasic(void* base, size_t width, size_t left, size_t right, int (*compar)(const void *, const void *));

#endif /* SORT_H */

