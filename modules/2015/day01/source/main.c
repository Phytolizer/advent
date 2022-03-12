#include "advent/line_iterator.h"
#include "advent/string.h"

#include <config.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int final_floor(advent_string_t line) {
    int floor = 0;
    for (size_t i = 0; i < line.length; i += 1) {
        if (line.data[i] == '(') {
            floor += 1;
        } else if (line.data[i] == ')') {
            floor -= 1;
        }
    }
    return floor;
}

static size_t when_on_floor(advent_string_t line, int target_floor) {
    int floor = 0;
    for (size_t i = 0; i < line.length; i += 1) {
        if (line.data[i] == '(') {
            floor += 1;
        } else if (line.data[i] == ')') {
            floor -= 1;
        }
        if (target_floor == floor) {
            return i + 1;
        }
    }
    return 0;
}

int main(void) {
    advent_line_iterator_t line_iter =
        advent_line_iterator_new(ADVENT_DAY_INPUT);
    if (line_iter.stream == NULL) {
        fprintf(stderr, "failed to open " ADVENT_DAY_INPUT "\n");
        exit(1);
    }
    for (advent_string_t line = advent_line_iterator_next(&line_iter);
         line.data != NULL; line = advent_line_iterator_next(&line_iter)) {
        printf("Instruction %zu: Floor %d\n", line_iter.which,
               final_floor(line));
        printf("On floor -1: %zu\n", when_on_floor(line, -1));
    }
    advent_line_iterator_close(&line_iter);
    return 0;
}
