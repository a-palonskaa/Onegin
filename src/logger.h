#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

enum LogLevel {
    DEBUG   = 0,
    INFO    = 1,
    WARNING = 2,
    ERROR   = 3
};

typedef struct {
    FILE* file_out;
    enum LogLevel min_level;
} logger_t;

void Log(enum LogLevel status, const char *fmt, ...);

void LoggerSetFile(FILE* out);

void LoggerSetLevel(enum LogLevel level);

const char* LogMessageTypePrint(enum LogLevel level, bool color);

void TimePrint(FILE *out);

void AestheticizeString(const char *src, char *dst, size_t max_len);

#endif /* LOGGER_H */
