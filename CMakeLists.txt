cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(TP2)
enable_language(C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
include_directories(inc)

add_subdirectory(src)