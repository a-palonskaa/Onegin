#include <stdio.h>
#include <stdlib.h>

#include "print.h"
#include "utf8_text.h"
#include "utf8_decode.h"

void PrintText(text_t* text, FILE* outstream) {
    char* buffer = (char*) calloc(text->symbols_amount * 4, sizeof(char));
    size_t buffer_len = 0;

    for (size_t j = 0; j < text->strings_amount; j++) {
        for (size_t i = 0; i < text->strings[j].length; i++) {
            buffer_len += EncodeSymbolUTF8(text->strings[j].runes[i], &buffer[buffer_len]);
            if (text->strings[j].runes[i] == 0x4) {
                buffer[--buffer_len] = '\0';
            }
        }
    }

    buffer[++buffer_len] = '\0';
    fputs(buffer, outstream);

    free(buffer);
    buffer = nullptr;
}
