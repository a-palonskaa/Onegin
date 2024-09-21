#ifndef MY_STR_FUNCTIONS_H
#define MY_STR_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

char* MyStrdup(const char *s1);
char* MyFgets(char* str, int size, FILE* stream);
char* MyStrcat(char* s1, const char* s2);
char* MyStrncat(char* s1, const char* s2, size_t n);
char* MyStrcpy(char* dst, const char* src);
char* MyStrncpy(char* dst, const char* src, size_t len);
char* MyStrchr(const char* s, int c);
size_t MyStrlen(const char *s);
size_t MyStrnlen(const char *s, size_t maxlen);
int MyPuts(const char *s);

#endif /* MY_STR_FUNCTIONS_H */
