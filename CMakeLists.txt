cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project("Ejovo lib")
enable_language(C)

include(CTest)

# enable_testing(ON)

# include(GNU)

# We must have the c implementation of pcg-c installed
# which can be found here: https://github.com/imneme/pcg-c
find_library(PCG_RANDOM_LIBRARY
    NAMES pcg_random 
    # REQUIRED
)

if (EXISTS ${PCG_RANDOM_LIBRARY})
    message("Found library: ${PCG_RANDOM_LIBRARY}")
    add_compile_options(-DPCG_RANDOM=1)
endif()




# If we actually found the library then when compiling use the flag -D

set(INC ${PROJECT_SOURCE_DIR}/inc)
set(SRC ${PROJECT_SOURCE_DIR}/src)
set(TEST ${PROJECT_SOURCE_DIR}/test)
set(BIN ${PROJECT_SOURCE_DIR}/bin)
set(LIB ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB})

# set(EJOVO_HEADERS ${CMAKE_})

add_compile_options(

    $<$<CONFIG:DEBUG>:-fno-omit-frame-pointer>
    $<$<CONFIG:DEBUG>:-Og>
    -Wall
    -Werror
    -Wextra
    -std=c11
    -Wno-unused-result
    # -fprofile-arcs
    # -ftest-coverage
    # --coverage
    # -g
    # -pg
    -O3

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
file(MAKE_DIRECTORY ${INC}/matrix)
# file(MAKE_DIRECTORY ${})

include_directories(${INC})
# include_directories(inc)
# include_directories(inc/battleship)
# include_directories(inc/matrix)

message("${INC} added to to include directories")

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(demo)

# add_custom_target( unit_tests ALL
#                     DEPENDS ${TESTS})

# Run tests after building the project
# add_custom_command(TARGET unit_tests
#                 COMMENT "Run tests"
#                 POST_BUILD COMMAND ctest --output-on-failure)
