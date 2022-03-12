#include "advent/line_iterator.h"
#include "advent/math.h"
#include "advent/string.h"

#include <assert.h>
#include <config.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint64_t length;
    uint64_t width;
    uint64_t height;
} present_t;

uint64_t wrap(present_t p) {
    uint64_t lw = p.length * p.width;
    uint64_t lh = p.length * p.height;
    uint64_t wh = p.width * p.height;
    uint64_t slack = min_u64(&lw, &lh, &wh, NULL);
    return 2 * lw + 2 * lh + 2 * wh + slack;
}

uint64_t ribbon(present_t p) {
    uint64_t lw = 2 * p.length + 2 * p.width;
    uint64_t lh = 2 * p.length + 2 * p.height;
    uint64_t wh = 2 * p.width + 2 * p.height;
    uint64_t bow = p.length * p.width * p.height;
    return bow + min_u64(&lw, &lh, &wh, NULL);
}

int main(void) {
    uint64_t paper = 0;
    uint64_t ribbon_length = 0;
    advent_line_iterator_t line_iter =
        advent_line_iterator_new(ADVENT_DAY_INPUT);
    if (line_iter.stream == NULL) {
        fprintf(stderr, "Failed opening " ADVENT_DAY_INPUT "\n");
        return 1;
    }
    for (advent_string_t line = advent_line_iterator_next(&line_iter);
         line.data != NULL; line = advent_line_iterator_next(&line_iter)) {
        advent_strings_t split_result = advent_string_split(line, 'x');
        assert(split_result.length == 3);
        long length = strtol(split_result.data[0].data, NULL, 10);
        long width = strtol(split_result.data[1].data, NULL, 10);
        long height = strtol(split_result.data[2].data, NULL, 10);
        present_t p = {length, width, height};
        paper += wrap(p);
        ribbon_length += ribbon(p);
        free(split_result.data);
    }

    printf("Total amount of paper to order: %" PRIu64 "\n", paper);
    printf("Total length of ribbon to order: %" PRIu64 "\n", ribbon_length);
    advent_line_iterator_close(&line_iter);
}
