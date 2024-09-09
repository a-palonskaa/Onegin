#ifndef TEXT_INF_LIB_H
#define TEXT_INF_LIB_H

#include <stdio.h>
#include <sys/stat.h>

size_t GetTextSymbolAmount(FILE* input_file);

size_t GetTextSymbolAmount(FILE* input_file) {
    struct stat file_data = {};
    fstat(fileno(input_file), &file_data); //REVIEW - нахуя off_t который long long,
    //ХУЙНЯ ПЕРЕДЕЛЫВАЙ - обарботать errno!!
    return (size_t) file_data.st_size;
}

#endif /* TEXT_INF_LIB_H */
