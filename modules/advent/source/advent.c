#include "advent.h"

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_CHUNK_SIZE 64

try_int64_t advent_getline(char** p_line, size_t* p_length, FILE* stream) {
    if (*p_line == NULL || *p_length == 0) {
        *p_length = LINE_CHUNK_SIZE;
        *p_line = malloc(LINE_CHUNK_SIZE);
        if (*p_line == NULL) {
            return (try_int64_t){.error = ENOMEM};
        }
    }
    size_t len = 0;
    while (true) {
        char* fgets_result =
            fgets(*p_line + len, (int)(*p_length - len), stream);
        len += strlen(*p_line + len);
        if (fgets_result == NULL) {
            return (try_int64_t){.value = (int64_t)len};
        }
        if ((*p_line)[len - 1] == '\n') {
            return (try_int64_t){.value = (int64_t)len - INT64_C(1)};
        }
        *p_length *= 2;
        char* new_buffer = realloc(*p_line, *p_length);
        if (new_buffer == NULL) {
            return (try_int64_t){.error = ENOMEM};
        }
        *p_line = new_buffer;
    }
}
