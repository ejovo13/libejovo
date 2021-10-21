cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(TP_ALL)
enable_language(C)
enable_testing(ON)

set(INC ${CMAKE_SOURCE_DIR}/inc)
set(SRC ${CMAKE_SOURCE_DIR}/src)
set(TEST ${CMAKE_SOURCE_DIR}/test)
set(BIN ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN})

add_compile_options(

    -Werror
    -Wimplicit
    -Wno-incompatible-pointer-types-discards-qualifiers

)

file(MAKE_DIRECTORY ${BIN})
# file(MAKE_DIRECTORY ${})

include_directories(${INC})

add_subdirectory(${SRC})
add_subdirectory(${TEST})

add_custom_target( unit_tests ALL
                    DEPENDS ${TESTS})

# Run tests after building the project
# add_custom_command(TARGET unit_tests
#                 COMMENT "Run tests"
#                 POST_BUILD COMMAND ctest --output-on-failure)
