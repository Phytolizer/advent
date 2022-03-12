#pragma once

#include <stddef.h>

typedef struct {
    char* data;
    size_t length;
} advent_string_t;

#define ADVENT_STRING(str, len)                                                \
    ((advent_string_t){.data = (str), .length = (len)})

typedef struct {
    advent_string_t* data;
    size_t length;
} advent_strings_t;

advent_strings_t advent_string_split(advent_string_t str, char delim);
