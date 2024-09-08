#ifndef DEFINE_CONSTANTS_H
#define DEFINE_CONSTANTS_H

#include <stdio.h>

const size_t MAX_STR_LEN = 40;
const size_t STR_CNT = 14;

typedef struct {
    char* str_begin;
    size_t str_len;
} strdata_t;

#endif /* DEFINE_CONSTANTS_H */
