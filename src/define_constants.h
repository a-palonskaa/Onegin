#ifndef DEFINE_CONSTANTS_H
#define DEFINE_CONSTANTS_H

#include <stdio.h>

#include "text_t_lib.h"

const size_t MAX_STR_LEN = 40;

typedef enum {
    FIRST = 0,
    LAST  = 1
} sort_mode_t;

typedef bool (*cmpr_mode_t) (size_t s1, size_t s2, string_t* text_strdata);

#endif /* DEFINE_CONSTANTS_H */

