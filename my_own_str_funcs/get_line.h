#ifndef MY_GET_LINE_V2_H
#define MY_GET_LINE_V2_H

#include <stdio.h>
#include <stdlib.h>

#define FREE(ptr) {    \
    free(ptr);         \
    ptr = nullptr;     \
}

ssize_t MYGetLineV2(char** lineptr, size_t* n, FILE* stream);

#endif /* MY_GET_LINE_V2_H */
