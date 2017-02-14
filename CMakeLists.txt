cmake_minimum_required(VERSION 3.5)
project(tinycore)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")

#include_directories("$ENV{HOME}/sdk/include")
include_directories("include")

FILE(GLOB_RECURSE SOURCE_FILES *.c *.h)
add_executable(tinycore ${SOURCE_FILES})