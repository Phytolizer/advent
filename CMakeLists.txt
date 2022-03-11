cmake_minimum_required(VERSION 3.20)
project(
    Advent
    VERSION 0.1.0
    DESCRIPTION "Advent of Code"
    HOMEPAGE_URL "https://github.com/Phytolizer/advent.git"
)

set(ADVENT_SRC advent.c)
list(TRANSFORM ADVENT_SRC PREPEND "modules/advent/source/")
add_library(advent ${ADVENT_SRC})
target_include_directories(advent PUBLIC "modules/advent/include")
