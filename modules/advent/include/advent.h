#pragma once

#include "advent/error_return.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef ADVENT_ERROR_RETURN(int64_t) try_int64_t;
try_int64_t advent_getline(char** p_line, size_t* p_capacity, FILE* stream);
