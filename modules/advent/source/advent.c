#include "advent.h"

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_CHUNK_SIZE 64

try_size_t advent_getline(char** p_line, size_t* p_capacity, FILE* stream) {
    if (*p_line == NULL || *p_capacity == 0) {
        *p_capacity = LINE_CHUNK_SIZE;
        *p_line = malloc(LINE_CHUNK_SIZE);
        if (*p_line == NULL) {
            return (try_size_t){.error = ENOMEM};
        }
    }
    (*p_line)[0] = '\0';
    size_t len = 0;
    while (true) {
        char* fgets_result =
            fgets(*p_line + len, (int)(*p_capacity - len), stream);
        len += strlen(*p_line + len);
        if (fgets_result == NULL) {
            return (try_size_t){.value = len};
        }
        if ((*p_line)[len - 1] == '\n') {
            return (try_size_t){.value = len - 1};
        }
        *p_capacity *= 2;
        char* new_buffer = realloc(*p_line, *p_capacity);
        if (new_buffer == NULL) {
            return (try_size_t){.error = ENOMEM};
        }
        *p_line = new_buffer;
    }
}
