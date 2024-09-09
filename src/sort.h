#ifndef SORT_H
#define SORT_H

#include <stdio.h>

#include "define_constants.h"

void StrBubbleSort(str_data_t* str_data, cmpr_mode_t CompareStr);
void StrQuickSort(str_data_t* str_data, size_t left, size_t right, cmpr_mode_t CompareStr);

#endif /* SORT_H */
