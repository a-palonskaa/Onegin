#ifndef SORT_H
#define SORT_H

#include <stdio.h>

#include "define_constants.h"

void StrBubbleSort(strdata_t* text_strdata, cmpr_mode_t CompareStr);
void StrQuickSort(strdata_t* text_strdata, size_t left, size_t right, cmpr_mode_t CompareStr);

#endif /* SORT_H */
