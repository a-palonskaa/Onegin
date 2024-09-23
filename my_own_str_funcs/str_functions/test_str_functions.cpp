#include <stdio.h>
#include <stdlib.h>

#include "str_functions.h"

int main() {
    char s1[5]= {};
    char p1[10] = {};

    s1[0] = 'm';
    s1[1] = 'a';
    s1[2] = 'k';
    s1[3] = 'e';
    s1[4] = '\n';

    const char* s2 = "hello world";

    printf("%s\n%s\n", s1, p1);
    printf("\n%d\n", MyStrlen(nullptr));
    printf("%s\n%s\n", s1, p1);
}
