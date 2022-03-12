#include "advent/line_iterator.h"

#include "advent.h"
#include "advent/string.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRBUF_SIZE 64

advent_line_iterator_t advent_line_iterator_new(const char* file_path) {
    return (advent_line_iterator_t){
        .stream = fopen(file_path, "r"),
        .line = NULL,
        .line_capacity = 0,
        .which = 0,
    };
}

advent_string_t advent_line_iterator_next(advent_line_iterator_t* iter) {
    try_size_t getline_result =
        advent_getline(&iter->line, &iter->line_capacity, iter->stream);
    if (getline_result.error != 0) {
        char errbuf[ERRBUF_SIZE];
        strerror_r(getline_result.error, errbuf, sizeof errbuf);
        fprintf(stderr, "advent_getline: %s\n", errbuf);
        exit(EXIT_FAILURE);
    }
    if (getline_result.value == 0) {
        return ADVENT_STRING(NULL, 0);
    }
    iter->which += 1;
    return ADVENT_STRING(iter->line, getline_result.value);
}

void advent_line_iterator_close(advent_line_iterator_t* iter) {
    fclose(iter->stream);
    free(iter->line);
}
