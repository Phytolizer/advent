#pragma once

#include <stddef.h>

typedef struct {
    char* data;
    size_t length;
} advent_string_t;

#define ADVENT_STRING(str, len)                                                \
    ((advent_string_t){.data = (str), .length = (len)})
