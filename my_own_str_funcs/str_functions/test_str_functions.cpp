#include <stdio.h>
#include <stdlib.h>

#include "str_functions.h"

int main() {
    char s1[5]= {};
    char p1[10] = {};

    s1[0] = 'm';
    s1[1] = 'e';
    s1[2] = 'o';
    s1[3] = 'w';
    s1[4] = '\n';

    const char* s2 = "yeah";

    printf("%s\n%s\n", s1, p1);

    printf("%s\n%s\n", s1, p1);
}
