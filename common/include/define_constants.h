#ifndef DEFINE_CONSTANTS_H
#define DEFINE_CONSTANTS_H

#include <stdio.h>
#include <cerrno>
#include <cstring>

#define STRERROR(ERRNO) ": %s", strerror(errno)

#define STATIC_ASSERT(COND,MSG)                           \
    do                                                    \
    {                                                     \
        typedef char static_assertion_##MSG[(COND)?1:-1]; \
        static_assertion_##MSG x_ = {};                   \
        (void) x_;                                        \
    } while (0)

#define FREE(ptr) {    \
    free(ptr);         \
    ptr = nullptr;     \
}

typedef enum {
    BUBBLE_SORT = 0,
    QUICK_SORT  = 1
} sort_type_t;

typedef enum {
    FORWARD  = 0,
    BACKWARD = 1,
    NO_SORT  = 2
}
sort_mode_t;

const size_t MAX_SORT_AMOUNT = 10;
const size_t DEFAULT_SORT_AMOUNT = 3;

typedef enum {
    DEFAULT = 0,
    COMPLEX = 1
} sort_state_t;

#endif /* DEFINE_CONSTANTS_H */
