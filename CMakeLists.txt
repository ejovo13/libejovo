cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(TP2)
enable_language(C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_compile_options(-Wall)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
include_directories(${CMAKE_SOURCE_DIR}/inc)

add_subdirectory(src)