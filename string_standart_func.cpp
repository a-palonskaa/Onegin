
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
