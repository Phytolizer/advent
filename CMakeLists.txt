cmake_minimum_required(VERSION 3.20)
project(
    Advent
    VERSION 0.1.0
    DESCRIPTION "Advent of Code"
    HOMEPAGE_URL "https://github.com/Phytolizer/advent.git"
)

set(ADVENT_SRC advent.c line_iterator.c)
list(TRANSFORM ADVENT_SRC PREPEND "modules/advent/source/")
add_library(advent ${ADVENT_SRC})
target_include_directories(advent PUBLIC "modules/advent/include")

function(advent_target NAME)
    cmake_parse_arguments(
        PARSE_ARGV 0 "ADVENT_TARGET" "" "" "EXTRA_SOURCES;EXTRA_LIBRARIES"
    )
    set(ADVENT_TARGET_SOURCES ${ADVENT_TARGET_EXTRA_SOURCES})
    list(APPEND ADVENT_TARGET_SOURCES main.c)
    list(TRANSFORM ADVENT_TARGET_SOURCES PREPEND "modules/${NAME}/source/")
    add_executable("${NAME}" ${ADVENT_TARGET_SOURCES})
    target_link_libraries(
        "${NAME}" PRIVATE advent ${ADVENT_TARGET_EXTRA_LIBRARIES}
    )
    target_compile_features("${NAME}" PRIVATE c_std_11)
    set(ADVENT_DAY_INPUT "${PROJECT_SOURCE_DIR}/modules/${NAME}/input.txt")
    configure_file("cmake/config.h.cin" "${NAME}-include/config.h")
    target_include_directories(
        "${NAME}" PRIVATE "${PROJECT_BINARY_DIR}/${NAME}-include"
    )
endfunction()

advent_target(day01 SOURCES main.c)
