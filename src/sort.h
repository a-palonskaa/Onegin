#ifndef SORT_H
#define SORT_H

#include <stdio.h>

void StringBubbleSort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
void StrQuickSort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
void StrQuickSortBasic(void *base, size_t left, size_t right, int (*compar)(const void *, const void *), size_t width);

#endif /* SORT_H */

