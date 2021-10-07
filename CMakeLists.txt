cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(TP3)
enable_language(C)
enable_testing(ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(INC ${CMAKE_SOURCE_DIR}/inc)
set(SRC ${CMAKE_SOURCE_DIR}/src)
set(TEST ${CMAKE_SOURCE_DIR}/test)

add_compile_options(-Wall)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
include_directories(${INC})

add_subdirectory(${SRC})
add_subdirectory(${TEST})

add_custom_target( unit_tests ALL
                    DEPENDS ${TESTS})

# Run tests after building the project
# add_custom_command(TARGET unit_tests
#                 COMMENT "Run tests"
#                 POST_BUILD COMMAND ctest --output-on-failure)