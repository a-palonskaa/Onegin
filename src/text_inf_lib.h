#ifndef TEXT_INF_LIB_H
#define TEXT_INF_LIB_H

#include <stdio.h>
#include <sys/stat.h>

size_t CountTextSymbols(FILE* input_file);
size_t CountTextLines(FILE* input_file);

size_t CountTextSymbols(FILE* input_file) {
    struct stat file_data = {};
    fstat(fileno(input_file), &file_data); //REVIEW - нахуя off_t который long long,
    //ХУЙНЯ ПЕРЕДЕЛЫВАЙ - обарботать errno!!
    return (size_t) file_data.st_size;
}

size_t CountTextLines(FILE* input_file) {
   size_t lines_cnt = 0;

   while (!feof(input_file)) {
        if (fgetc(input_file) == '\n') {
            lines_cnt++;
        }
    }

    fseek(input_file, 0, 0);
   return lines_cnt;
}

#endif /* TEXT_INF_LIB_H */
