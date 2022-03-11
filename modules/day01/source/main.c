#include "advent/line_iterator.h"

#include <config.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    advent_line_iterator_t line_iter =
        advent_line_iterator_new(ADVENT_DAY_INPUT);
    if (line_iter.stream == NULL) {
        fprintf(stderr, "failed to open " ADVENT_DAY_INPUT "\n");
        exit(1);
    }
    while (true) {
        char* line = advent_line_iterator_next(&line_iter);
        if (line == NULL) {
            break;
        }
        printf("%.*s\n", (int)line_iter.line_length, line);
    }
    advent_line_iterator_close(&line_iter);
    return 0;
}
