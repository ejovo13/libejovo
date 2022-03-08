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

)

add_library(ejovo_matrix OBJECT ${EJOVO_MATRIX_SRC})
target_include_directories(ejovo_matrix PUBLIC ${INC}/matrix)
set_target_properties(ejovo_matrix PROPERTIES
    HEADER_DIRS
        ${INC}/matrix

)