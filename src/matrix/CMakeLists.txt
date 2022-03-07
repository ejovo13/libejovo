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

)

add_library(ejovo_matrix OBJECT ${EJOVO_MATRIX_SRC})
target_include_directories(ejovo_matrix PRIVATE ${INC}/matrix)