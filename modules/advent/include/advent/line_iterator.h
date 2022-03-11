#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    FILE* stream;
    char* line;
    size_t line_length;
    size_t line_capacity;
    size_t which;
} advent_line_iterator_t;

advent_line_iterator_t advent_line_iterator_new(FILE* stream);
bool advent_line_iterator_is_ok(const advent_line_iterator_t* iter);
char* advent_line_iterator_next(advent_line_iterator_t* iter);
void advent_line_iterator_close(advent_line_iterator_t* iter);
