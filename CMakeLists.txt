cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(TP_ALL)
enable_language(C)
enable_testing(ON)

set(INC ${CMAKE_SOURCE_DIR}/inc)
set(SRC ${CMAKE_SOURCE_DIR}/src)
set(TEST ${CMAKE_SOURCE_DIR}/test)
set(BIN ${CMAKE_SOURCE_DIR}/bin)
set(LIB ${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB})

# set(EJOVO_HEADERS ${CMAKE_})

add_compile_options(

    # -Wall
    # -Werror
    # -Wimplicit
    # -Wno-incompatible-pointer-types-discards-qualifiers
    # -fprofile-arcs
    # -ftest-coverage
    # --coverage
    # -g
    # -pg

)

add_link_options(
    # -fprofile-arcs
    # -ftest-coverage
    # --coverage
    # -g
    # -pg
    # -lgcov
)

file(MAKE_DIRECTORY ${BIN})
file(MAKE_DIRECTORY ${LIB})
# file(MAKE_DIRECTORY ${})

include_directories(${INC})
include_directories(inc)
include_directories(inc/battleship)
include_directories(inc/matrix)

add_subdirectory(src)
add_subdirectory(test)

add_custom_target( unit_tests ALL
                    DEPENDS ${TESTS})

# Run tests after building the project
# add_custom_command(TARGET unit_tests
#                 COMMENT "Run tests"
#                 POST_BUILD COMMAND ctest --output-on-failure)
