#include <assert.h>
#include <sys/stat.h>
#include <string.h>

#include "logger.h"
#include "text_t_lib.h"

ssize_t FindFileSize(FILE* input_file) {
    assert(input_file != nullptr);

    struct stat file_data = {};

    if (fstat(fileno(input_file), &file_data) == -1) {
        perror("FAILED TO READ THE FILE\n");
        return -1;
    }

    if (file_data.st_size == 0) {
        Log(WARNING, "EMPTY FILE");
    }

    return (ssize_t) file_data.st_size;
}

ssize_t CountTextSymbols(FILE* input_file) {
    assert(input_file != nullptr);

    if (fseek(input_file, 0, SEEK_END)) {
        perror("FAILED TO MOVE POINTER IN THE FILE\n");
        return -1;
    }

    ssize_t size = (ssize_t) ftell(input_file);
    if (size == -1) {
        perror("POINTER POSITION IN THE FILE INDICATION ERROR\n");
    }

    if (fseek(input_file, 0, SEEK_SET)) {
        perror("FAILED TO MOVE POINTER IN THE FILE\n");
        return -1;
    }

    return (ssize_t) size;
}



size_t CountTextLines(text_t* text) {
    assert(text != nullptr);

    size_t last_newline_index = 0;
    size_t lines_cnt = 0;

    for (size_t i = 0; i < text->symbols_amount; i++) {
        if (text->symbols[i] == '\n') {
            lines_cnt++;
            last_newline_index = i;
        }
    }

    if (text->symbols_amount - last_newline_index > 1) {
        lines_cnt++;
    }

    return lines_cnt;
}

void ParseText(text_t* text) {
    assert(text != nullptr);

    size_t j = 0;
    const size_t str_cnt = text->strings_amount;
    const size_t smb_cnt = text->symbols_amount;
//ХУЙНЯ - или через memcpy эти массивчики перекопировать?? //функция копирования структуры
    text->nonsorted_strings[j].begin = text->symbols;
    text->backward_sorted_strings[j].begin = text->symbols;
    text->forward_sorted_strings[j].begin  = text->symbols;

    j++;

    for (size_t i = 0; i < smb_cnt && j < str_cnt; i++) {
        if (text->symbols[i] == '\n') {
            text->nonsorted_strings[j].begin = &text->symbols[i+1];
            text->backward_sorted_strings[j].begin = text->nonsorted_strings[j].begin;
            text->forward_sorted_strings[j].begin  = text->nonsorted_strings[j].begin;

            text->nonsorted_strings[j - 1].length = (size_t) (text->nonsorted_strings[j].begin -
                                                              text->nonsorted_strings[j - 1].begin);
            text->backward_sorted_strings[j - 1].length = text->nonsorted_strings[j - 1].length;
            text->forward_sorted_strings[j - 1].length  = text->nonsorted_strings[j - 1].length;

            text->symbols[i] = '\0';
            j++;
        }
    }

    if (text->symbols[smb_cnt - 2] == '\n') {
        text->symbols[smb_cnt - 2] = '\0';
    }

    text->nonsorted_strings[str_cnt - 1].length = (size_t) (&text->symbols[smb_cnt - 1] -
                                                            text->nonsorted_strings[str_cnt - 1].begin);
    text->backward_sorted_strings[str_cnt - 1].length = text->nonsorted_strings[str_cnt - 1].length;
    text->forward_sorted_strings[str_cnt - 1].length  = text->nonsorted_strings[str_cnt - 1].length;
}

error_t StringCtor(text_t* text, FILE* input_file) {
    assert(input_file != nullptr);
    assert(text != nullptr);

    unsigned int calloc_cnt = 0;
    ssize_t symbols_amount = FindFileSize(input_file);

    if (symbols_amount == -1) {
        return FILE_READ_ERROR;
    }

    symbols_amount++;

    text->symbols_amount = (size_t) symbols_amount;

    text->symbols = (char*) calloc(text->symbols_amount, sizeof(char));
    if (text->symbols == nullptr) {
        perror("FAILED TO ALLOCATE THE MEMORY\n");
        return MEMORY_ALLOCATE_ERROR;
    }

    calloc_cnt++;

    if ((fread(text->symbols, sizeof(char), text->symbols_amount, input_file) != text->symbols_amount) &&
         !feof(input_file) &&
         ferror(input_file)) {
        perror("FILE READ ERROR\n");
        StringDtor(text);
        return FILE_READ_ERROR;
    }

    if (fseek(input_file, 0, SEEK_SET)) {
        StringDtor(text);
        perror("FAILED TO MOVE POINTER IN THE FILE\n");
        return INFILE_PTR_MOVING_ERROR;
    }

    calloc_cnt++;

    text->strings_amount = CountTextLines(text);

    text->nonsorted_strings = (string_t*) calloc(text->strings_amount, sizeof(string_t));
    if (text->nonsorted_strings == nullptr) {
        StringDtor(text);
        perror("FAILED TO ALLOCATE THE MEMORY\n");
        return MEMORY_ALLOCATE_ERROR;
    }

    calloc_cnt++;

    text->forward_sorted_strings = (string_t*) calloc(text->strings_amount, sizeof(string_t));
    if (text->forward_sorted_strings == nullptr) {
        StringDtor(text);
        perror("FAILED TO ALLOCATE THE MEMORY\n");
        return MEMORY_ALLOCATE_ERROR;
    }

    calloc_cnt++;

    text->backward_sorted_strings = (string_t*) calloc(text->strings_amount, sizeof(string_t));
    if (text->backward_sorted_strings == nullptr) {
        StringDtor(text);
        perror("FAILED TO ALLOCATE THE MEMORY\n");
        return MEMORY_ALLOCATE_ERROR;
    }

    calloc_cnt++;

    ParseText(text);
    return NO_ERRORS;
}

void StringDtor(text_t* text) {
    assert(text != nullptr);

    free(text->backward_sorted_strings);
    text->backward_sorted_strings = nullptr;

    free(text->forward_sorted_strings);
    text->forward_sorted_strings = nullptr;

    free(text->nonsorted_strings);
    text->nonsorted_strings = nullptr;

    free(text->symbols);
    text->symbols = nullptr;

    text->strings_amount = 0;
    text->symbols_amount = 0;
}

void GetTextSymbols(text_t* text, FILE* input_file) {
    assert(text != nullptr);
    assert(input_file != nullptr);

    int c = 0;

    for (size_t i = 0; i < text->symbols_amount && ((c = fgetc(input_file)) != EOF); i++) {
        text->symbols[i] = (char) c;
    }

    text->symbols[text->symbols_amount - 1] = '\0';
}
