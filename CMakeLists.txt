cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(TP1)
enable_testing(ON)
enable_language(C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_compile_options(-Wall)

add_subdirectory(src)
