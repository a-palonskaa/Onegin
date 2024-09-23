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

#endif /* LOGGER_H */
