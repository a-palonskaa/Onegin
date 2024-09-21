#ifndef GET_LINE_H
#define GET_LINE_H

#include <stdio.h>
#include <stdlib.h>

#define FREE(ptr) {    \
    free(ptr);         \
    ptr = nullptr;     \
}

ssize_t MYGetLineV2(char** lineptr, size_t* n, FILE* stream);

#endif /* GET_LINE_H */
