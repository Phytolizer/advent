#include "advent/string.h"

#include <stdlib.h>
#include <string.h>

advent_strings_t advent_string_split(advent_string_t str, char delim) {
    advent_strings_t result = {0};

    size_t delim_count = 0;
    for (size_t i = 0; i < str.length; i += 1) {
        if (str.data[i] == delim) {
            delim_count += 1;
        }
    }

    result.length = delim_count + 1;
    result.data = malloc(result.length * sizeof(advent_string_t));
    char* split_start = str.data;
    for (size_t i = 0; i < delim_count; i += 1) {
        char* split_end = strchr(split_start, delim);
        result.data[i].data = split_start;
        result.data[i].length = split_end - split_start;
        split_start = split_end + 1;
    }
    result.data[result.length - 1].data = split_start;
    result.data[result.length - 1].length =
        (str.data + str.length) - split_start;
    return result;
}
