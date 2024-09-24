#include <stdlib.h>

#include "define_consts.h"
#include "read_utf8.h"

void TextDtor(text_t* text) {
    for (size_t i = 0; i < text->strings_amount; i++) {
        free(text->strings[i].runes);
        text->strings[i].runes = nullptr;
    }

    free(text->strings);
    text->strings = nullptr;
}
