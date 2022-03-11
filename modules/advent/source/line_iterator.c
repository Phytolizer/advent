#include "advent/line_iterator.h"

#include "advent.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRBUF_SIZE 64

advent_line_iterator_t advent_line_iterator_new(const char* file_path) {
    return (advent_line_iterator_t){
        .stream = fopen(file_path, "r"),
        .line = NULL,
        .line_length = 0,
        .line_capacity = 0,
        .which = 0,
    };
}

char* advent_line_iterator_next(advent_line_iterator_t* iter) {
    try_size_t getline_result =
        advent_getline(&iter->line, &iter->line_capacity, iter->stream);
    if (getline_result.error != 0) {
        char errbuf[ERRBUF_SIZE];
        strerror_r(getline_result.error, errbuf, sizeof errbuf);
        fprintf(stderr, "advent_getline: %s\n", errbuf);
        exit(EXIT_FAILURE);
    }
    if (getline_result.value == 0) {
        return NULL;
    }
    iter->line_length = getline_result.value;
    return iter->line;
}

void advent_line_iterator_close(advent_line_iterator_t* iter) {
    fclose(iter->stream);
    free(iter->line);
}
