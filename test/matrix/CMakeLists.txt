set(MATRIX_TEST_SRC

    mat_vec
    mat_getset
    mat_iter




)

foreach(T ${MATRIX_TEST_SRC})
    ejovo_add_test(${T})
endforeach(T)