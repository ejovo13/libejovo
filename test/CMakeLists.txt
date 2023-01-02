list(APPEND TESTS
    is_substr
    cpy_str
    reverse_str
    supprime_espaces
    del_substr
    parentheses
    substr
    words
    matrix
    # lab
    complex
    mathad_speed
    matcopy
    mathad_copy
    matcmp_speed
    computational
    matcopycol
    all_mat
    time
    pcg
    benchmark
    img
    # vidTest
    # rand
)

if (${FFMPEG_FOUND})

list(APPEND TESTS vidTest)
endif()


list(APPEND TEST_LIBS
    ejovo
)

# if (NOT WIN32)
#     list(APPEND TEST_LIBS m)
# endif()

list(APPEND TEST_INC
    ${INC}
)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}/test)

# set(TEST_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)

macro(ejovo_add_test TESTNAME)

    # create an exectuable in which the tests will be stored
    set(TEST_BIN "test_${TESTNAME}")

    # message(STATUS "Adding test ${TESTNAME}")
    add_executable(${TEST_BIN} "${TESTNAME}.c")
    target_link_libraries(${TEST_BIN} ${TEST_LIBS})
    target_include_directories(${TEST_BIN} PUBLIC ${TEST_INC})
    target_compile_options(${TEST_BIN} PUBLIC -g -O3)
    # target_compile_options(${TEST_BIN} PUBLIC -g -O0)
    set_target_properties(${TEST_BIN}
        PROPERTIES
        # OUTPUT_NAME ${TESTNAME}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    add_test(${TESTNAME} test_${TESTNAME})

endmacro()

add_subdirectory(matrix)

macro (copy_file filename)
    file (
        COPY ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

foreach(T ${TESTS})
    ejovo_add_test(${T})
endforeach(T)

copy_file(f0.pgm)
copy_file(f1.pgm)
copy_file(mbf0.pgm)
copy_file(mbf1.pgm)
copy_file(c60.pgm)
copy_file(c60t.pgm)
copy_file(f35.pgm)
copy_file(f36.pgm)
copy_file(f37.pgm)
copy_file(chess_long.mp4)
copy_file(draco.avi)
copy_file(draco2.avi)
copy_file(melee_move.mp4)
copy_file(melee.mp4)
copy_file(test.mp4)

# ============================================
#            Google tests
# ============================================
# include(GoogleTest)

# # Add source file of tests
# macro(gtest_add_src src_name) 
#     add_executable(${src_name} ${src_name}.cc)
#     target_link_libraries(${src_name} GTest::gtest_main ejovo)
#     target_link_directories(${src_name} PUBLIC ${TEST_INC})
#     gtest_discover_tests(${src_name} hello_gtest)
# endmacro()

# add_executable(hello_gtest hello_gtest.cc)
# target_link_libraries(hello_gtest GTest::gtest_main ejovo)
# target_link_directories(hello_gtest PUBLIC ${TEST_INC})
# gtest_discover_tests(hello_gtest)



# Flags for profiling on local machine

# target_compile_options(test_mathad_speed PUBLIC -pg -g)
# target_link_options(test_mathad_speed PUBLIC -pg -g)
# target_compile_options(test_matcmp_speed PUBLIC -pg -g)
# target_link_options(test_matcmp_speed PUBLIC -pg -g)