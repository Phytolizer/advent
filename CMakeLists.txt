cmake_minimum_required(VERSION 3.20)
project(
    Advent
    VERSION 0.1.0
    DESCRIPTION "Advent of Code"
    HOMEPAGE_URL "https://github.com/Phytolizer/advent.git"
)

include(FindPkgConfig)
include(FetchContent)

pkg_search_module(PCRE2 libpcre2-8)
if(NOT PCRE2_FOUND)
    FetchContent_Declare(
        pcre2
        GIT_REPOSITORY "https://github.com/PhilipHazel/pcre2.git"
        GIT_TAG "pcre2-10.39"
    )
    FetchContent_MakeAvailable(pcre2)
endif()

set(ADVENT_SRC advent.c line_iterator.c math.c string.c)
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
    string(REPLACE "/" "_" TARGET_NAME "${NAME}")
    add_executable("${TARGET_NAME}" ${ADVENT_TARGET_SOURCES})
    target_link_libraries(
        "${TARGET_NAME}" PRIVATE advent ${ADVENT_TARGET_EXTRA_LIBRARIES}
    )
    target_compile_features("${TARGET_NAME}" PRIVATE c_std_11)
    set(ADVENT_DAY_INPUT "${PROJECT_SOURCE_DIR}/modules/${NAME}/input.txt")
    configure_file("cmake/config.h.cin" "${NAME}-include/config.h")
    target_include_directories(
        "${TARGET_NAME}" PRIVATE "${PROJECT_BINARY_DIR}/${NAME}-include"
    )
    target_compile_definitions(
        "${TARGET_NAME}" PRIVATE "PCRE2_CODE_UNIT_WIDTH=8"
    )
endfunction()

advent_target(2015/day01)
advent_target(2015/day02)
