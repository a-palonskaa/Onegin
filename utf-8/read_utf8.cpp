#include <assert.h>

#include "read_utf8.h"

const size_t MEMORY_BLOCK = 5;

error_t ReadStrings(string_t* string, FILE* instream) {
    assert(string != nullptr);
    assert(instream != nullptr);

    size_t strlen = 0;
    size_t calloced_memory_length = MEMORY_BLOCK;
    size_t rune_t_size = sizeof(my_rune_t);
    string->runes = (my_rune_t*) calloc(MEMORY_BLOCK, rune_t_size);
    bool eos_flag = false;
    error_t read_octet_flag = NO_ERRORS;

    while (!eos_flag) {
        while ((strlen < calloced_memory_length - 1 &&
                (read_octet_flag = ReadOctetsUTF8(&string->runes[strlen], instream)) != END_OF_FILE) &&
                DecodeSymbolUTF8(&string->runes[strlen]) != 0xA) {
            strlen++;
        }
        if (strlen >= calloced_memory_length - 1) {
            calloced_memory_length += MEMORY_BLOCK;
            string->runes = (my_rune_t*) realloc(string->runes, calloced_memory_length * rune_t_size);
        }
        else {
            string->runes[strlen].code = 0xA;
            string->runes[strlen].bits = 0xA000000;
            string->runes[strlen].width = 1;
            strlen++;
            eos_flag = true;
        }
    }
    string->length = strlen;
    return read_octet_flag;
}

void ReadText(text_t* text, FILE* instream) {
    size_t calloced_memory_length = MEMORY_BLOCK;
    size_t string_t_size = sizeof(string_t);
    text->strings = (string_t*) calloc(MEMORY_BLOCK, string_t_size);
    bool eof_flag = false;
    size_t string_cnt = 0;

    while (!eof_flag) {
        while ((string_cnt < calloced_memory_length - 1 &&
                ReadStrings(&text->strings[string_cnt], instream) != END_OF_FILE)) {
            string_cnt++;
        }

        if (string_cnt >= calloced_memory_length - 1) {
            calloced_memory_length += MEMORY_BLOCK;
            text->strings = (string_t*) realloc(text->strings, calloced_memory_length * string_t_size);
        }
        else {
            eof_flag = true;
        }
    }

    text->strings_amount = string_cnt;
}
//ХУЙНЯ ПЕРЕДЕЛЫВАЙ - realloc at the end to cut unneccesary memory
