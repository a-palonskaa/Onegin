
//Как реализовать свап
//через calloc

// void* sd = calloc(width, 1);
// memcpy(sd, s1, width);
//     memcpy(s1, s2, width);
//         memcpy(s2, sd, width);
// free(sd);

//побайтовое копирование (привести к char* и width раз свапнуть)
//кастовать к большим типам если возможно (width) unsigned long long ->

// uint8_t     в битах
// uint16_t
// uint32_t
// uint64_t

// перевести йыщке к такому прототипу
// void
// qsort(void *base, size_t elements_cnt, size_t sizeof, int (*compar)(const void *, const void *));


void StrBubbleSort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) ;
void SwapStringsTest(void* s1, void* s2, size_t width);
int CompareStringsForwardTest(const void *s1, const void *s2);

int CompareStringsForwardTest(const void *s1, const void *s2) {
//знаю какая структура
    assert(s1 != nullptr);
    assert(s2 != nullptr);

    size_t i = 0;
    size_t j = 0;

    SkipNonAlphaSymbols(&i, s1, FIRST);
    SkipNonAlphaSymbols(&j, s2, FIRST);

    while (*(s1 + i) != '\0' && *(s2 + j) != '\0' &&
           tolower(*(s1 + i)) == tolower(*(s2 + j)) {
        i++;
        j++;

        SkipNonAlphaSymbols(&i, s1, FIRST);
        SkipNonAlphaSymbols(&j, s2, FIRST);
    }

    return (tolower(s1) > tolower(s2))  ? 1 :
           (tolower(s1) == tolower(s2)) ? 0 : -1
}

void StrBubbleSort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
//адрес на массив структур
    for (size_t i = 0; i < nel; i++) {
        for (size_t j = i + 1; j < nel; j++) {
            if (сompar(((char*) base + i * width), ((char*) base + j * width)))) {
                SwapStringsTest(((char*) base + i * width), ((char*) base + j * width)), width);
            }
        }
    }
}

void SwapStringsTest(void* s1, void* s2, size_t width) {
    void* sd = calloc(width, 1);
    memcpy(sd, s1, width);
    memcpy(s1, s2, width);
    memcpy(s2, sd, width);
    free(sd);
}
