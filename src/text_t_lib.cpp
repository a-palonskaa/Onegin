#include <assert.h>
#include <sys/stat.h>

#include "text_t_lib.h"

ssize_t CountTextSymbols(FILE* input_file) {
    assert(input_file != nullptr);

    struct stat file_data = {};

    if (fstat(fileno(input_file), &file_data) == -1) {
        perror("FAILED TO READ THE FILE\n");
        return -1;
    }

    if (file_data.st_size == 0) {
        perror("EMPTY FILE\n");
        return 0;
    }

    return (ssize_t) file_data.st_size;
}

// ssize_t CountTextSymbolsTest(FILE* input_file) {
//     assert(input_file != nullptr);
//
//     fseek(input_file, 0L, SEEK_END);
//     ssize_t size = (ssize_t) ftell(input_file);
//     printf("%d", size);
//     return (ssize_t) size;
// }



size_t CountTextLines(text_t* text) {
    assert(text != nullptr);

    size_t last_enter_symbol = 0;
    size_t lines_cnt = 0;
    size_t i = 0;

    for (; i < text->symbols_amount; i++) {
        if (text->symbols[i] == '\n') {
            lines_cnt++;
            last_enter_symbol  = i;
        }
    }

    if (text->symbols_amount - last_enter_symbol > 2) {
        lines_cnt++;
    }

    return lines_cnt;
}

void IndexStrings(text_t* text) {
    assert(text != nullptr);

    size_t j = 0;
    const size_t str_cnt = text->strings_amount;
    const size_t smb_cnt = text->symbols_amount;

    text->strings[j++].begin = text->symbols;

    for (size_t i = 0; i < smb_cnt && j < str_cnt; i++) {
        if (text->symbols[i] == '\n') {
            text->strings[j].begin = &text->symbols[i+1];
            text->strings[j - 1].length = (size_t) (text->strings[j].begin - text->strings[j - 1].begin);
            text->symbols[i] = '\0';
            j++;
        }
    }
    text->strings[str_cnt - 1].length = (size_t) (&text->symbols[smb_cnt - 1] - text->strings[str_cnt - 1].begin);
}

error_t StringCtor(text_t* text, FILE* input_file) {
    assert(input_file != nullptr);
    assert(text != nullptr);

    ssize_t symbols_amount = CountTextSymbols(input_file);

    if (symbols_amount == -1) {
        return FILE_READ_ERROR;
    }
    else if (symbols_amount == 0) {
        return EMPTY_FILE_ERROR;
    }
    text->symbols_amount = (size_t) symbols_amount;

    text->symbols = (char*) calloc(text->symbols_amount, sizeof(char));

    if (text->symbols == nullptr) {
        perror("FAILED TO ALLOCATE THE MEMORY\n");
        return MEMORY_ALLOCATE_ERROR;
    }

    if ((fread(text->symbols, sizeof(char), text->symbols_amount, input_file) != text->symbols_amount) &&
         !feof(input_file) &&
         ferror(input_file)) {
        free(text->symbols);
        text->symbols = nullptr;
        return FILE_READ_ERROR;
    }

    if (fseek(input_file, 0, SEEK_SET)) {
        perror("FAILED TO MOVE POINTER IN THE FILE\n");
        return INFILE_PTR_MOVING_ERROR;
    };

    text->strings_amount = CountTextLines(text);

    text->strings = (string_t*) calloc(text->strings_amount, sizeof(string_t));

    if (text->strings == nullptr) {
        free(text->symbols);
        text->symbols = nullptr;

        perror("FAILED TO ALLOCATE THE MEMORY\n");
        return MEMORY_ALLOCATE_ERROR;
    }

    IndexStrings(text);
    return NO_ERRORS;
}

void StringDtor(text_t* text) {
    assert(text != nullptr);

    free(text->symbols);
    text->symbols = nullptr;

    free(text->strings);
    text->strings = nullptr;

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

