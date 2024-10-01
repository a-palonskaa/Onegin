#include <stdio.h>
#include "utf8_decode.h"
#include "define_consts.h"
#include "read_utf8.h"
#include "text_t.h"
#include "print.h"

int main() {
    my_rune_t rune = {};
    FILE* instream = fopen("in.txt", "r");
    FILE* outstream = fopen("out.txt", "w");
    text_t text = {};

    ReadText(&text, instream);

    printf("amount of the strings is %zu\n", text.strings_amount);
    printf("amount of the symbols is %zu\n", text.symbols_amount);

    PrintText(&text, outstream);

    TextDtor(&text);
}
