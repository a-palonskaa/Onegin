#include <assert.h>
#include <sys/stat.h>
#include <string.h>

#include "logger.h"
#include "utf8_text.h"
#include "define_constants.h"

const size_t MEMORY_BLOCK = 5000;

ssize_t FindFileSize(FILE* input_file) {
    assert(input_file != nullptr);

    struct stat file_data = {};

    if (fstat(fileno(input_file), &file_data) == -1) {
        Log(ERROR, "FAILED TO READ THE FILE\n" STRERROR(errno));
        return -1;
    }

    if (file_data.st_size == 0) {
        Log(WARNING, "EMPTY FILE\n" STRERROR(errno));
    }

    Log(INFO, "FILE SIZE: %zu\n", file_data.st_size);
    return (ssize_t) file_data.st_size;
}

ssize_t ReadStrings(text_t* text, size_t string_cnt, size_t in_bytes_cnt, FILE* instream) {
    my_rune_t new_rune = {};
    assert(text != nullptr);
    assert(instream != nullptr);

    string_t* string = &text->strings[string_cnt];
    size_t strlen = 0;
    size_t bytes_cnt = in_bytes_cnt;
    size_t calloced_memory_length = MEMORY_BLOCK;
    string->runes = (uint32_t*) calloc(MEMORY_BLOCK, sizeof(uint32_t));
    bool eos_flag = false;
    errors_t read_octet_flag = NOERRORS;

    while (!eos_flag) {
        while ((strlen < calloced_memory_length - 1 &&
               (read_octet_flag = ReadOctetsUTF8(&new_rune, &text->buffer[bytes_cnt])) != END_OF_FILE) &&
                DecodeSymbolUTF8(&new_rune) != 0xA) {
            string->runes[strlen++] = new_rune.code;
            bytes_cnt += new_rune.width;
        }
        if (read_octet_flag == LENGTH_ENCODE_ERROR) {
            return -1;
        }
        if (strlen >= calloced_memory_length - 1) {
            calloced_memory_length += MEMORY_BLOCK;
            string->runes = (uint32_t*) realloc(string->runes, calloced_memory_length * sizeof(uint32_t));
        }
        else {
            string->runes[strlen] = 0xA;
            bytes_cnt += 1;
            strlen++;
            eos_flag = true;
        }
    }
    string->length = strlen;
    return (ssize_t) (bytes_cnt -  in_bytes_cnt);
}

error_t ParseText(text_t* text, FILE* instream) {
    assert(text != nullptr);
    assert(instream != nullptr);

    size_t string_t_size = sizeof(string_t);
    size_t string_cnt = 0;
    size_t bytes_cnt = 0;
    ssize_t str_len = 0;
    bool eof_flag = false;

    size_t calloced_memory_length = (size_t) text->bytes_amount / 40;
    text->strings = (string_t*) calloc(calloced_memory_length, string_t_size);
    if (text->strings == nullptr) {
        StringDtor(text);
        Log(ERROR, "FAILED TO ALLOCATE THE MEMORY\n" STRERROR(errno));
        return MEMORY_ALLOCATE_ERROR;
    }

    while (!eof_flag) {

        while (string_cnt < calloced_memory_length - 1 &&
               bytes_cnt < text->bytes_amount) {
            str_len = ReadStrings(text, string_cnt, bytes_cnt, instream);
            if (str_len == -1) {
                return SYMBOLS_DECODING_ERROR;
            }
            bytes_cnt += (size_t) ReadStrings(text, string_cnt, bytes_cnt, instream);
            text->symbols_amount += text->strings[string_cnt++].length;
        }

        if (string_cnt >= calloced_memory_length - 1) {
            calloced_memory_length += MEMORY_BLOCK;
            text->strings = (string_t*) realloc(text->strings, calloced_memory_length * string_t_size);
            if (text->strings == nullptr) {
                StringDtor(text);
                Log(ERROR, "FAILED TO ALLOCATE THE MEMORY\n" STRERROR(errno));
                return MEMORY_ALLOCATE_ERROR;
            }
        }
        else {
            eof_flag = true;
        }
    }
    text->strings_amount = string_cnt;
    return NO_ERRORS;
}

error_t StringCtor(text_t* text, FILE* input_file) {
    assert(input_file != nullptr);
    assert(text != nullptr);

    ssize_t bytes_amount = FindFileSize(input_file);
    if (bytes_amount == -1) {
        return FILE_READ_ERROR;
    }
    text->bytes_amount = (size_t) bytes_amount;

    text->buffer = (unsigned char*) calloc(text->bytes_amount, sizeof(unsigned char));
    if (text->buffer == nullptr) {
        StringDtor(text);
        Log(ERROR, "FAILED TO ALLOCATE THE MEMORY\n" STRERROR(errno));
        return MEMORY_ALLOCATE_ERROR;
    }

    ssize_t position_in_file = ftell(input_file);
    if (position_in_file == -1) {
        return PTR_POSITION_INDICATION_ERROR;
    }

    if (fseek(input_file, 0, SEEK_SET)) {
        Log(ERROR, "FAILED TO MOVE POINTER IN THE FILE\n" STRERROR(errno));
        StringDtor(text);
        return INFILE_PTR_MOVING_ERROR;
    }

    if ((fread(text->buffer, sizeof(unsigned char), text->bytes_amount, input_file) != text->bytes_amount) &&
         !feof(input_file) &&
         ferror(input_file)) {
        Log(ERROR, "FILE READ ERROR\n" STRERROR(errno));
        StringDtor(text);
        return FILE_READ_ERROR;
    }

    if (fseek(input_file, position_in_file, SEEK_SET)) {
        Log(ERROR, "FAILED TO MOVE POINTER IN THE FILE\n" STRERROR(errno));
        StringDtor(text);
        return INFILE_PTR_MOVING_ERROR;
    }

    error_t text_parse_error_status = ParseText(text, input_file);
    if (text_parse_error_status != NO_ERRORS) {
        return text_parse_error_status;
    }

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

    free(text->buffer);
    text->buffer = nullptr;

    text->strings_amount = 0;
    text->symbols_amount = 0;
    Log(INFO, "TEXT STRUCTURE WAS SUCCESSFULLY DESTRUCTED\n");
}
