#ifndef SORT_H
#define SORT_H

#include <stdio.h>

#include "define_constants.h"

//void StrQuickSort(text_t* text, size_t left, size_t right, cmpr_mode_t сompare_str);
void StringBubbleSort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));

#endif /* SORT_H */

