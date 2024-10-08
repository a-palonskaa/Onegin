#include "get_line_v1.h"

ssize_t MYGetLineV1(char** lineptr, size_t* n, FILE* stream) {
    size_t buffer_size = 10;
    int symbol = 0;

    if (*lineptr == nullptr) {
        *lineptr = (char*) calloc(buffer_size, sizeof(char));
        if (*lineptr == nullptr) {
            return -1;
        }
    }
    else {
        *lineptr = (char*) realloc(*lineptr, buffer_size * sizeof(char));
    }

    size_t cnt = 0;
    while ((symbol = fgetc(stream)) != '\n' && symbol != EOF) {
        if (cnt >= buffer_size - 2) {
            buffer_size += 10;

            char* newlineptr = (char*) realloc(*lineptr, buffer_size * sizeof(char));
            if (newlineptr == nullptr) {
                free(newlineptr);
                newlineptr = nullptr;
                return -1;
            }

            *lineptr = newlineptr;
        }
        (*lineptr)[cnt++] = (char) symbol;
    }

    (*lineptr)[cnt] = '\n';
    (*lineptr)[cnt + 1] = '\0';
    *n = cnt + 1;

    return (ssize_t) cnt + 1;
}
