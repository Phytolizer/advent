#include "advent/line_iterator.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {
    advent_line_iterator_t line_iter = advent_line_iterator_new(stdin);
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
