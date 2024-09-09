#ifndef DEFINE_CONSTANTS_H
#define DEFINE_CONSTANTS_H

#include <stdio.h>

const size_t MAX_STR_LEN = 40;

typedef struct {
    char* str_begin;
    size_t str_len;
} str_store_data_t;

typedef struct {
    str_store_data_t* str_store_data;
    const size_t str_cnt;
} str_data_t;

typedef enum {
    FIRST = 0,
    LAST  = 1
} sort_mode_t;

typedef bool (*cmpr_mode_t) (size_t s1, size_t s2, str_store_data_t* text_strdata);

#endif /* DEFINE_CONSTANTS_H */
