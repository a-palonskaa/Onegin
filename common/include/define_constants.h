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

#endif /* DEFINE_CONSTANTS_H */
