#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "get_line_v1.h"

#define FREE(ptr) {    \
    free(ptr);         \
    ptr = nullptr;     \
}

int main() {

    char* ptr = nullptr;
    size_t n = 0;

    FILE* stream = fopen("text.txt", "r");

    if (stream == nullptr) {
        return EXIT_FAILURE;
    }

    printf("%s", ptr);
    fseek(stream, 0, SEEK_SET);
    clock_t t1 = clock();
    getline(&ptr, &n, stream);
    clock_t t2 = clock();

    clock_t t3 = clock();
    MYGetLineV1(&ptr, &n, stream);
    clock_t t4 = clock();

    fseek(stream, 0, SEEK_SET);

    printf("%s", ptr);

    printf("Working time of standart get line = %ld\n", t2 - t1);
    printf("Working time of MY get line = %ld\n", t4 - t3);

    FREE(ptr);

    if (fclose(stream) == EOF) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
