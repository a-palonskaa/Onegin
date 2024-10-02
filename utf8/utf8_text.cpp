#include <assert.h>
#include <sys/stat.h>
#include <string.h>

#include "logger.h"
#include "utf8_text.h"

const size_t MEMORY_BLOCK = 200000;

errors_t ReadStrings(string_t* string, FILE* instream) {
    my_rune_t new_rune = {};
    assert(string != nullptr);
    assert(instream != nullptr);

    size_t strlen = 0;
    size_t calloced_memory_length = MEMORY_BLOCK;
    string->runes = (uint32_t*) calloc(MEMORY_BLOCK, sizeof(uint32_t));
    bool eos_flag = false;
    errors_t read_octet_flag = NOERRORS;

    while (!eos_flag) {
        while ((strlen < calloced_memory_length - 1 &&
               (read_octet_flag = ReadOctetsUTF8(&new_rune, instream)) != END_OF_FILE) &&
                DecodeSymbolUTF8(&new_rune) != 0xA) {
            string->runes[strlen] = new_rune.code;
            strlen++;
        }
        if (strlen >= calloced_memory_length - 1) {
            calloced_memory_length += MEMORY_BLOCK;
            string->runes = (uint32_t*) realloc(string->runes, calloced_memory_length * sizeof(uint32_t));
        }
        else {
            string->runes[strlen] = 0xA;
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
            text->symbols_amount += text->strings[string_cnt++].length;
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

error_t StringCtor(text_t* text, FILE* input_file) {
    assert(input_file != nullptr);
    assert(text != nullptr);

    ReadText(text, input_file);

    Log(INFO, "TEXT STRUCTURE WAS SUCCESSFULLY CREATED AND INITIALIZED\n");
    return NO_ERRORS;
}

void StringDtor(text_t* text) {
    assert(text != nullptr);

    for (size_t i = 0; i < text->strings_amount; i++) {
        free(text->strings[i].runes);
        text->strings[i].runes = nullptr;
    }

    free(text->strings);
    text->strings = nullptr;

    text->strings_amount = 0;
    text->symbols_amount = 0;
    Log(INFO, "TEXT STRUCTURE WAS SUCCESSFULLY DESTRUCTED\n");
}
