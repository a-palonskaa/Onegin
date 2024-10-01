#include "get_line.h"

ssize_t MYGetLineV2(char** lineptr, size_t* n, FILE* stream) {
    static const size_t MAX_STR_SIZE = 100;
    static char* buffer = (char*) calloc(MAX_STR_SIZE, sizeof(char));
    static size_t buffer_size = MAX_STR_SIZE;
    static size_t cnt = 0;

    size_t end_str = 0;
    size_t start_str = cnt;
    static bool no_eof_flag = 1;
    size_t read_cnt = 0;

    if (cnt == 0) {
        read_cnt = fread(buffer, sizeof(char), MAX_STR_SIZE, stream);

        no_eof_flag = !feof(stream);
    }
    do {
        if (cnt >= buffer_size - 1 && no_eof_flag) {
            buffer = (char*) realloc(buffer, buffer_size + MAX_STR_SIZE);
            read_cnt = fread(buffer + buffer_size, sizeof(char), MAX_STR_SIZE, stream);
            no_eof_flag = !feof(stream);
            buffer_size += read_cnt;
        }
        while(cnt < (buffer_size - 1) && buffer[cnt] != '\n' && buffer[cnt] != '\0') {
            cnt++;
        }
    } while (buffer[cnt] != '\n' && no_eof_flag && buffer[cnt] != '\0');

    if (buffer[cnt] == '\0') {
        return -1;
    }

    end_str = ++cnt;

    if ((*lineptr = (char*) realloc(*lineptr, (end_str - start_str + 1) * sizeof(char))) == nullptr) {
        return -1;
    }

    for (size_t i = 0; i < end_str - start_str; i++) {
        (*lineptr)[i] = buffer[start_str + i];
    }

    (*lineptr)[end_str - start_str] = '\0';
    *n = end_str - start_str + 1;

    return (ssize_t) (end_str - start_str);
}
