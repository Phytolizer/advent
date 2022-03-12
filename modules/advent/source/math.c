#include "advent/math.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

uint64_t min_u64(const uint64_t* p1, ...) {
    uint64_t result = *p1;
    va_list args;
    va_start(args, p1);
    for (const uint64_t* p = va_arg(args, const uint64_t*); p != NULL;
         p = va_arg(args, const uint64_t*)) {
        if (result > *p) {
            result = *p;
        }
    }
    va_end(args);
    return result;
}
