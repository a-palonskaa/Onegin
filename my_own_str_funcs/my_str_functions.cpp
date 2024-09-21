#include "my_str_functions.h"

char* MyStrdup(const char *s1) {
    size_t length = 0;

    while (s1[length++] != '\0') {
        ;
    }

    char* s1_copy = (char*) calloc(length, sizeof(char));
    if (s1_copy == nullptr) {
        return nullptr;
    }

    for (size_t i = 0; i < length; i++) {
        s1_copy[i] = s1[i];
    }
    //memcpy(s1_copy, s1, length);

    return s1_copy;
}

char* MyFgets(char* str, int size, FILE* stream) {
    int c = 0;
    int i = 0;

    while (i < size - 1 && (c = getc(stream)) != EOF && c != '\n') {
        str[i++] = (char) c;
    }

    if (!i) {
        return nullptr;
    }

    str[i] = '\0';
    return str;
}

char* MyStrcat(char* s1, const char* s2) {
    size_t i = 0;

    while(s1[i] != '\0') {
        i++;
    }

    for (size_t j = 0; s2[j] != '\0'; j++, i++) {
        s1[i] = s2[j];
    }

    s1[i] = '\0';
    return s1;
}


char* MyStrncat(char* s1, const char* s2, size_t n) {
    size_t i = 0;

    while(s1[i] != '\0') {
        i++;
    }

    for (size_t j = 0; j < n && s2[j] != '\0'; j++, i++) {
        s1[i] = s2[j];
    }

    s1[i] = '\0';
    return s1;
}

char* MyStrcpy(char* dst, const char* src) {
    size_t i = 0;

    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }

    dst[i] = '\0';
    return dst;
}

char* MyStrncpy(char* dst, const char* src, size_t len) {
    size_t i = 0;

    while (i < len && src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    if (src[i] == '\0') {
        dst[i] = '\0';
    }
    else {
        while (i < len) {
            dst[i++] = '\0';
        }
    }

    return dst;
}

char* MyStrchr(const char* s, int c) {
    size_t i = 0;
    c = (char) c;

    while ((s[i] != '\0') && (s[i] != c)) {
        i++;
    }

    if (c != '\0' && s[i] == '\0') {
        return nullptr;
    }
    return (char*) &s[i];
};

