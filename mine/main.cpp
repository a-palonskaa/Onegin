#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_get_line_v2.h"

int main() {

    char* ptr = nullptr;
    size_t n = 0;

    FILE* stream = fopen("text.txt", "r");

    if (stream == nullptr) {
        Log(ERROR, "FILE OPEN ERROR\n", STRERROR(errno));
        return EXIT_FAILURE;
    }
    time_t t1 = clock();
    getline(&ptr, &n, stream);
    printf("%s", ptr);
    time_t t2 = clock();
    fseek(stream, 0, SEEK_SET);

    MYGetLineV2(&ptr, &n, stream);
    printf("%s", ptr);

    time_t t3 = clock();
    printf("Working time of standart get line = %ld\n", t2 - t1);
    printf("Working time of MY get line = %ld\n", t3 - t2);

    FREE(ptr);

    if (fclose(stream) == EOF) {
        Log(ERROR, "FILE OPEN ERROR\n", STRERROR(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
