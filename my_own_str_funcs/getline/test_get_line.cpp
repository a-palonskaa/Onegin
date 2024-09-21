#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "get_line.h"

int main() {

    char* ptr = nullptr;
    size_t n = 0;

    FILE* stream = fopen("text.txt", "r");

    if (stream == nullptr) {
        return EXIT_FAILURE;
    }

    clock_t t1 = clock();
    getline(&ptr, &n, stream);
    printf("%s", ptr);
    clock_t t2 = clock();

    fseek(stream, 0, SEEK_SET);

    clock_t t3 = clock();
    MYGetLineV2(&ptr, &n, stream);
    printf("%s", ptr);
    clock_t t4 = clock();

    printf("Working time of standart get line = %ld\n", t2 - t1);
    printf("Working time of MY get line = %ld\n", t4 - t3);

    FREE(ptr);

    if (fclose(stream) == EOF) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
