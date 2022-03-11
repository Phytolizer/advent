#pragma once

#define ADVENT_ERROR_RETURN(T)                                                 \
    struct {                                                                   \
        int error;                                                             \
        T value;                                                               \
    }
