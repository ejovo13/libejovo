set(MATRIX_TEST_SRC

    mat_vec
    mat_getset
    mat_iter
    mat_lin
    mat_core
    mat_stats
    mat_dist
    mat_log
    mat_func
    mat_index
    mat_generic


)

foreach(T ${MATRIX_TEST_SRC})
    ejovo_add_test(${T})
endforeach(T)