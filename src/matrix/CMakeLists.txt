set(EJOVO_MATRIX_SRC

    matrix_core.c
    matrix_foreach.c
    matrix_state.c
    matrix_vector.c
    matrix_linear.c
    matrix_getset.c
    matrix_compute.c
    matrix_iter.c
    matrix_special.c
    matrix_stats.c
    matrix_dist.c
    matrix_functional.c
    matrix_logical.c
    matrix_index.c
    matrix_stochastic.c
    matrix_getset.c

)

file(MAKE_DIRECTORY ${INC}/matrix)

add_library(ejovo_matrix_double OBJECT ${EJOVO_MATRIX_SRC})
# add_library(ejovo_matrix_int OBJECT ${EJOVO_MATRIX_SRC})
# add_library(ejovo_matrix_float OBJECT ${EJOVO_MATRIX_SRC})

target_compile_definitions(ejovo_matrix_double PUBLIC FIRST_COMPILATION_PASS)
# target_compile_definitions(ejovo_matrix_int PUBLIC MATRIX_TYPE=int)
# target_compile_definitions(ejovo_matrix_float PUBLIC MATRIX_TYPE=float)

target_include_directories(ejovo_matrix_double PUBLIC ${INC}/matrix)
# target_include_directories(ejovo_matrix_int PUBLIC ${INC}/matrix)
# target_include_directories(ejovo_matrix_float PUBLIC ${INC}/matrix)


# set_target_properties(ejovo_matrix PROPERTIES
#     HEADER_DIRS
#         ${INC}/matrix

# )