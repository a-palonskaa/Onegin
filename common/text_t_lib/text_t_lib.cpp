#include <assert.h>
#include <sys/stat.h>
#include <string.h>

#include "logger.h"
#include "text_t_lib.h"

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

ssize_t CountTextSymbols(FILE* input_file) {
    assert(input_file != nullptr);

    if (fseek(input_file, 0, SEEK_END)) {
        Log(WARNING, "FAILED TO MOVE POINTER IN THE FILE\n" STRERROR(errno));
        return -1;
    }

    ssize_t size = (ssize_t) ftell(input_file);
    if (size == -1) {
        Log(WARNING, "POINTER POSITION IN THE FILE INDICATION ERROR\n" STRERROR(errno));
    }

    if (fseek(input_file, 0, SEEK_SET)) {
        Log(WARNING, "FAILED TO MOVE POINTER IN THE FILE\n" STRERROR(errno));
        return -1;
    }

    Log(INFO, "FILE SIZE: %zu\n",  size);
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

    Log(INFO, "LINES AMOUNT: %zu\n", lines_cnt);
    return lines_cnt;
}

void ParseText(text_t* text) {
    assert(text != nullptr);

    size_t j = 0;
    const size_t str_cnt = text->strings_amount;
    const size_t smb_cnt = text->symbols_amount;
    string_t* string = nullptr;

    if (text->sort_state == DEFAULT) {
        string = text->strings.non_sorted;
    }
    else {
        string = text->strings.sorted[0];
    }

    string[j].begin = text->symbols;
    j++;

    for (size_t i = 0; i < smb_cnt && j < str_cnt; i++) {
        if (text->symbols[i] == '\n') {
            string[j].begin = &text->symbols[i+1];
            string[j - 1].length = (size_t) (string[j].begin - string[j - 1].begin);
            text->symbols[i] = '\0';
            j++;
        }
    }

    string[str_cnt - 1].length = (size_t) (&text->symbols[smb_cnt - 1] -
                                            string[str_cnt - 1].begin);

    if (text->sort_state == DEFAULT) {
        Log(INFO, "TEXT WAS SUCCESSFULLY PARSED\n");
        return;
    }

    for (size_t i = 1; i < SORT_TYPES_CNT; i++) {
        CopyStrings(string, text->strings.sorted[i], str_cnt);
    }

    Log(INFO, "TEXT WAS SUCCESSFULLY PARSED\n");
}

error_t StringCtor(text_t* text, FILE* input_file) {
    assert(input_file != nullptr);
    assert(text != nullptr);

    ssize_t symbols_amount = FindFileSize(input_file);

    if (symbols_amount == -1) {
        return FILE_READ_ERROR;
    }

    symbols_amount++;

    text->symbols_amount = (size_t) symbols_amount;

    text->symbols = (char*) calloc(text->symbols_amount, sizeof(char));
    if (text->symbols == nullptr) {
        Log(ERROR, "FAILED TO ALLOCATE THE MEMORY\n" STRERROR(errno));
        return MEMORY_ALLOCATE_ERROR;
    }

    if ((fread(text->symbols, sizeof(char), text->symbols_amount, input_file) != text->symbols_amount) &&
         !feof(input_file) &&
         ferror(input_file)) {
        Log(ERROR, "FILE READ ERROR\n" STRERROR(errno));
        StringDtor(text);
        return FILE_READ_ERROR;
    }

    if (fseek(input_file, 0, SEEK_SET)) {
        StringDtor(text);
        Log(ERROR, "FAILED TO MOVE POINTER IN THE FILE\n" STRERROR(errno));
        return INFILE_PTR_MOVING_ERROR;
    }

    text->strings_amount = CountTextLines(text);
    if (text->sort_state == DEFAULT) {
        text->strings.non_sorted = (string_t*) calloc(text->strings_amount, sizeof(string_t));

        if (text->strings.non_sorted == nullptr) {
            StringDtor(text);
            Log(ERROR, "FAILED TO ALLOCATE THE MEMORY\n" STRERROR(errno));
            return MEMORY_ALLOCATE_ERROR;
        }
    }
    else {
        text->strings.sorted = (string_t**) calloc(SORT_TYPES_CNT, sizeof(string_t*));

        if (text->strings.sorted == nullptr) {
            StringDtor(text);
            Log(ERROR, "FAILED TO ALLOCATE THE MEMORY\n" STRERROR(errno));
            return MEMORY_ALLOCATE_ERROR;
        }

        size_t i = 0;

        for(;i < SORT_TYPES_CNT; i++) {
            text->strings.sorted[i] = (string_t*) calloc(text->strings_amount, sizeof(string_t));

            if (text->strings.sorted[i] == nullptr) {
            StringDtor(text);
            Log(ERROR, "FAILED TO ALLOCATE THE MEMORY\n" STRERROR(errno));
            return MEMORY_ALLOCATE_ERROR;
        }
        }
    }

    ParseText(text);
    Log(INFO, "TEXT STRUCTURE WAS SUCCESSFULLY CREATED AND INITIALIZED\n");
    return NO_ERRORS;
}

void StringDtor(text_t* text) {
    assert(text != nullptr);

    if (text->sort_state == DEFAULT) {
        free(text->strings.non_sorted);
        text->strings.non_sorted = nullptr;
    }
    else {
        for (size_t i = 0; i < SORT_TYPES_CNT; i++) {
            free(text->strings.sorted[i]);
            text->strings.sorted[i] = nullptr;
        }
    }

    free(text->symbols);
    text->symbols = nullptr;

    text->strings_amount = 0;
    text->symbols_amount = 0;
    Log(INFO, "TEXT STRUCTURE WAS SUCCESSFULLY DESTRUCTED\n");
}

void GetTextSymbols(text_t* text, FILE* input_file) {
    assert(text != nullptr);
    assert(input_file != nullptr);

    int c = 0;

    for (size_t i = 0; i < text->symbols_amount && ((c = fgetc(input_file)) != EOF); i++) {
        text->symbols[i] = (char) c;
    }

    text->symbols[text->symbols_amount - 1] = '\0';
    Log(INFO, "TEXT WAS SUCCESSFULLY READ\n");
}

void CopyStrings(string_t* src, string_t* dst, size_t str_cnt) {
    size_t size_of_string_t = sizeof(string_t);
    for (size_t i = 0; i < str_cnt; i++) {
        memcpy(&dst[i], &src[i],  size_of_string_t);
    }
}
