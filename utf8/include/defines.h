#ifndef DEFINES_H
#define DEFINES_H

typedef struct {
    uint32_t bits;
    uint32_t code;
    size_t width;
} my_rune_t;

typedef struct {
    uint32_t* runes;
    size_t length;
} string_t;

typedef struct {
    size_t strings_amount;
    size_t symbols_amount;
    string_t* strings;
} text_t;

#endif /* DEFINES_H */
