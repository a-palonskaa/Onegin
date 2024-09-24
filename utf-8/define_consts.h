#ifndef DEFINE_CONSTS_H
#define DEFINE_CONSTS_H

typedef struct {
    uint32_t bits;
    uint32_t code;
    size_t width;
} my_rune_t;

typedef struct {
    my_rune_t* runes;
    size_t length;
} string_t;

typedef struct {
    string_t* strings;
    size_t strings_amount;
    size_t symbols_amount;
} text_t;
//TODO -   validation of the symbols, то что в первом байте не больше 4 елиниц и код непревышает максимальново кода.

#endif /* DEFINE_CONSTS_H */
