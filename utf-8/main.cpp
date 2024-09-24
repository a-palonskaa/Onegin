#include <stdio.h>
#include "utf8_decode.h"
#include "define_consts.h"
#include "read_utf8.h"
#include "text_t.h"

int main() {
    my_rune_t rune = {};
    FILE* instream = fopen("utf8_in.txt", "r");
    FILE* outstream = fopen("utf8_code.txt", "w");
    text_t text = {};

    ReadText(&text, instream);

    printf("amount of the strings is %zu\n", text.strings_amount);

    for (size_t j = 0; j < text.strings_amount; j++) {
        for (size_t i = 0; i < text.strings[j].length; i++) {
            PrintSymbolUTF8(&(text.strings[j].runes[i]), outstream);
        }
    }

    TextDtor(&text);
}
