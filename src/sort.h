#ifndef SORT_H
#define SORT_H

#include <stdio.h>

#include "define_constants.h"

void StrBubbleSort(text_t* text, cmpr_mode_t сompare_str);
void StrQuickSort(text_t* text, size_t left, size_t right, cmpr_mode_t сompare_str);

#endif /* SORT_H */

