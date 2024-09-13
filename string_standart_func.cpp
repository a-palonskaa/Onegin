// void* sd = calloc(width, 1);
// memcpy(sd, s1, width);
//     memcpy(s1, s2, width);
//         memcpy(s2, sd, width);
// free(sd);

// qsort(void *base, size_t elements_cnt, size_t sizeof, int (*compar)(const void *, const void *));

// man new - не смотреть, гуглить
// int* a = new int(5);
// delete a;
// string_t* s = new string_t(file);
// delete s;

// string_t* s = nullptr;
// NewString(&s, file);
// string_t* s = NewString(file); calloc на структуру, пот7ом ctor
//объект либо построен полностью либо никак, если на каком-то этапе не выделилась памть, я чищу всё предыдущее и выхожу(руками, не деструктором)
// DeleteString(&s);, dtor, потом очистить s(string_*) т.е  в обратном порядке(работает с консистентными объектами)

//fseek, feof, fgetc


// void StrQuickSort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
// void StrQuickSort(void *base, size_t left, size_t right, int (*compar)(const void *, const void *)){
//     if (left >= right) {
//         return;
//     }
//
//     SwapStrings(left, (left + right) / 2, text->strings);
//
//     size_t last = left;
//
//     for(size_t i = left + 1; i <= right; i++) {
//         if (compar(((char*) base + i * width), ((char*) base + left * width)) == 1) {
//             SwapStrings(((char*) base + (++last) * width), ((char*) base + i * width), width);
//         }
//     }
//
//     SwapStrings(left, last, text->strings);
//
//     StrQuickSort(text, left, last, сompare_str);
//     StrQuickSort(text, last + 1, right, сompare_str);
// }
// void StrQuickSort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
//     if (nel <= 1) {
//         return;
//     }
//
//     SwapStrings(0, (nel - 1) / 2, text->strings);
//
//     size_t last = 0;
//
//     for(size_t i = ; i <= nel - 1; i++) {
//         if (compar(((char*) base + i * width), (char*) base) == 1) {
//             SwapStrings(((char*) base + (++last) * width), ((char*) base + i * width), width);
//         }
//     }
//
//     SwapStrings(0, last, text->strings);
//
//     StrQuickSort(base, nel - 1, width, сompare_str);
// }

