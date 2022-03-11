#pragma once

#include "advent/error_return.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef ADVENT_ERROR_RETURN(size_t) try_size_t;
try_size_t advent_getline(char** p_line, size_t* p_capacity, FILE* stream);
