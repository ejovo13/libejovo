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
    # img
    # rand
)

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



foreach(T ${TESTS})
    ejovo_add_test(${T})
endforeach(T)

# Flags for profiling on local machine

# target_compile_options(test_mathad_speed PUBLIC -pg -g)
# target_link_options(test_mathad_speed PUBLIC -pg -g)
# target_compile_options(test_matcmp_speed PUBLIC -pg -g)
# target_link_options(test_matcmp_speed PUBLIC -pg -g)