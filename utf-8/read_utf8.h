#ifndef READ_UTF8_H
#define READ_UTF8_H

#include <stdio.h>
#include "utf8_decode.h"
#include "define_consts.h"

error_t ReadStrings(string_t* text, FILE* instream);
void ReadText(text_t* text, FILE* instream);

#endif /* READ_UTF8_H */
