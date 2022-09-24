#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

void t_mat_alloc();
void t_matrix_new();
void t_matrix_move();
void t_matrix_from();
void t_matrix_colvec();
void t_matrix_rowvec();
void t_matrix_valid_bounds();
void t_matrix_at();
void t_matrix_access();
void t_matrix_print();
void t_mat_setcol();
void t_mat_setrow();
void t_matrix_set_row();
void t_matrix_set_col();
void t_matrix_get_row();
void t_matrix_get_col();
void t_matrix_times_vec();

void t_matrix_foreach();

void t_matrix_scalar();
void t_matrix_matrix();
void t_vecnorm();
void t_vector_normalize();
void t_vector_inner();
void t_ColIter();
void t_mat_normcols();

void t_matrix_mask();
void t_matrix_pow();


int main() {

    t_mat_alloc();
    t_matrix_new();
    t_matrix_move();
    t_matrix_from();
    t_matrix_colvec();
    t_matrix_rowvec();
    t_matrix_valid_bounds();
    t_matrix_at();
    t_matrix_access();
    t_matrix_print();
    t_mat_setrow();
    t_mat_setcol();
    t_matrix_set_row();
    t_matrix_set_col();
    t_matrix_get_row();
    t_matrix_get_col();
    t_matrix_times_vec();

    t_matrix_foreach();

    t_matrix_scalar();
    t_matrix_matrix();
    t_vecnorm();
    t_vector_normalize();
    t_vector_inner();
    // t_ColIter();
    t_mat_normcols();

    t_matrix_mask();
    t_matrix_pow();



    return 0;
}

// verify that allocating various sizes of a matrix doesn't lead to a malloc error
void t_mat_alloc() {

    MATRIX_T *m1 = MAT_FN(alloc)(10, 15);
    MATRIX_T *m2 = MAT_FN(alloc)(1000, 50);
    MATRIX_T *m3 = MAT_FN(alloc)(10000, 10000);

    assert(m1);
    assert(m2);
    assert(m3);

    assert(m1->nrows == 10 && m1->ncols == 15);
    assert(m2->nrows == 1000 && m2->ncols == 50);
    assert(m3->nrows == 10000 && m3->ncols == 10000);

    MATRIX_FN(free)(m1);
    MATRIX_FN(free)(m2);
    MATRIX_FN(free)(m3);
    printf("t_matalloc passed\n");

}

// Verify allocations with MATRIX_FN(new)
void t_matrix_new() {

    MATRIX_T *m1 = MATRIX_FN(new)(10, 15);
    MATRIX_T *m2 = MATRIX_FN(new)(1000, 50);
    MATRIX_T *m3 = MATRIX_FN(new)(10000, 10000);

    MATRIX_T *m4 = MATRIX_FN(new)(-10, -10);

    assert(m1);
    assert(m2);
    assert(m3);
    assert(m4);

    assert(m1->nrows == 10 && m1->ncols == 15);
    assert(m2->nrows == 1000 && m2->ncols == 50);
    assert(m3->nrows == 10000 && m3->ncols == 10000);

    assert(m4->nrows == 0 && m4->ncols == 0);

    MATRIX_FN(free)(m1);
    MATRIX_FN(free)(m2);
    MATRIX_FN(free)(m3);
    MATRIX_FN(free)(m4);

    printf("t_MATRIX_FN(new) passed\n");
}

void t_matrix_move() {

    MATRIX_TYPE arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    MATRIX_TYPE *arr_ptr = (MATRIX_TYPE *) arr;
    MATRIX_TYPE arr_copy[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // ARR_PTR HAS BEEN NULLIFIED!!!!!!!!!
    printf("Address of arr_ptr before call: %p\n", arr_ptr);
    printf("Address of arr before call: %p\n", arr);
    MATRIX_T *m = MATRIX_FN(move)(&arr_ptr, 3, 3); // moving a local variable, if m
                                         // persists out side of this call, it is dead
    // MATRIX_T *m1 = MATRIX_FN(move)(arr, 1, 9); // THIS IS SUPER DANGEROUS, THESE TWO ARRAYS
                                             // ARE POINTING TO THE SAME BLOCK OF DATA
                                             // PREFER TO USE MATRIX_CLONE_ARRAY


    printf("Address of arr_ptr: %p\n", arr_ptr);
    printf("Address of m->data: %p\n", m->data);
    // ASSERT THAT ARR_PTR IS NULL
    assert(!arr_ptr);


    // Verify that the two matrices are identical (and are using the same data)
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            assert(MAT_FN(at)(m, i, j) == arr_copy[i * 3 + j]);
            // assert(MAT_FN(acc)(m, i, j) == MAT_FN(acc)(m1, 0, i * 3 + j)); // Verify that the pointers are in fact identical
        }
    }

    printf("t_MATRIX_FN(from_arr) passed\n");

}

void t_matrix_from() {

    MATRIX_TYPE arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    MATRIX_T *m = MATRIX_FN(from)(arr, 3, 3);
    MATRIX_T *m1 = MATRIX_FN(from)(arr, 1, 9); // This time were are creating a new copy
                                              // and the resources are not shared

    MATRIX_FN(set)(m1, 0, 3, -50);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {

            if (i == 1 && j == 0) {
                assert(MATRIX_FN(at)(m, i, j) == arr[i * 3 + j]);
                assert(MATRIX_FN(at)(m1, 0, i * 3 + j) != arr[i * 3 + j]); // we modified m1 so make sure that it is different
                assert(MATRIX_FN(access)(m, i, j) != MATRIX_FN(access)(m1, 0, i * 3 + j)); // make sure the pointes are different.
            } else {

                assert(MATRIX_FN(at)(m, i, j) == arr[i * 3 + j]);
                assert(MATRIX_FN(at)(m1, 0, i * 3 + j) == arr[i * 3 + j]); // we modified m1 so make sure that it is different
                assert(MATRIX_FN(access)(m, i, j) != MATRIX_FN(access)(m1, 0, i * 3 + j)); // make sure the pointes are different.

            }
        }
    }

    printf("t_MATRIX_FN(clone_arr) passed\n");
}

void t_matrix_colvec() {

    MATRIX_TYPE arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    MATRIX_T *m = MATRIX_FN(colvec)(arr, 9);

    assert(m);

    // MATRIX_FN(print)(m);

    MATRIX_FN(free)(m);

}

void t_matrix_rowvec() {

    MATRIX_TYPE arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    MATRIX_T *m = MATRIX_FN(rowvec)(arr, 9);

    assert(m);

    // MATRIX_FN(print)(m);

    MATRIX_FN(free)(m);
}



// Bounds are 0-indexed
void t_matrix_valid_bounds() {

    MATRIX_T *m1 = MATRIX_FN(new)(50, 25);

    assert(MATRIX_FN(valid_bounds)(m1, 0, 0));
    assert(MATRIX_FN(valid_bounds)(m1, 10, 10));
    assert(MATRIX_FN(valid_bounds)(m1, 30, 10));
    assert(MATRIX_FN(valid_bounds)(m1, 49, 10));
    assert(MATRIX_FN(valid_bounds)(m1, 23, 24));
    assert(MATRIX_FN(valid_bounds)(m1, 49, 24));

    assert(!MATRIX_FN(valid_bounds)(m1, 10, 30));
    assert(!MATRIX_FN(valid_bounds)(m1, 50, 10));
    assert(!MATRIX_FN(valid_bounds)(m1, 49, 25));
    assert(!MATRIX_FN(valid_bounds)(m1, -3, 13));

    printf("t_MATRIX_FN(valid_bounds) passed\n");
}

// If out of bounds return -1
void t_matrix_at() {

    MATRIX_T *m1 = MATRIX_FN(new)(10, 10);

    for (size_t i = 0; i < m1->nrows; i++) {
        for (size_t j = 0; j < m1->ncols; j++) {

            assert(MATRIX_FN(at)(m1, i, j) == 0);
            assert(MAT_FN(at)(m1, i, j) == 0);
        }
    }

    assert(MATRIX_FN(at)(m1, 0, -3) == -1); // this will warn stderr that we are trying to access an unacceptable bound

    MATRIX_FN(free)(m1);
    printf("t_MATRIX_FN(valid_bounds) passed\n");
}

void t_matrix_set() {

    MATRIX_T *m1 = MATRIX_FN(new)(3, 3);
    MATRIX_T *m2 = MATRIX_FN(new)(3, 3);

    MATRIX_TYPE arr[] = {1, 2, 3, 56, 7, 45, 23, 76, 23};
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            MATRIX_FN(set)(m1, i, j, arr[i * 3 + j]);
            MAT_FN(set)(m2, i, j, arr[i * 3 + j]);
        }
    }

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            assert(MATRIX_FN(at)(m1, i, j) == arr[i * 3 + j]);
            assert(MAT_FN(at)(m2, i, j) == arr[i * 3 + j]);
        }
    }

    MATRIX_FN(free)(m1);
    MATRIX_FN(free)(m2);

    printf("t_MATRIX_FN(set) passed\n");

}

void t_matrix_access() {

    MATRIX_T *m1 = MATRIX_FN(new)(15, 15);

    MATRIX_FN(set)(m1, 13, 4, 1.0);

    MATRIX_TYPE *el_ptr = MATRIX_FN(access)(m1, 13, 4);
    MATRIX_TYPE *el_ptr_nocheck = MAT_FN(acc)(m1, 13, 4);

    assert(el_ptr == el_ptr_nocheck);
    assert(*el_ptr == 1.0);

    el_ptr = MATRIX_FN(access)(m1, 15, 15);
    assert(!el_ptr); // make sure that upon a bad access request el_ptr returns null

    MATRIX_FN(free)(m1);

    printf("t_MATRIX_FN(access) passed\n");

}

// Requires manual inspection
void t_matrix_print() {

    MATRIX_T *m1 = MATRIX_FN(new)(5, 13);
    MATRIX_FN(print)(m1);

    assert(true);
    MATRIX_FN(free)(m1);

}

void t_mat_cdr() {

    MATRIX_TYPE data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    MATRIX_TYPE data2[] = {4, 2, 5, 1, 9, 8, 3, 2, 1, 2, 4, 5};


    MATRIX_T *m1 = MATRIX_FN(from)(data, 3, 3);
    MATRIX_T *m2 = MATRIX_FN(from)(data2, 3, 3);



}

void t_mat_setrow() {

    MATRIX_T *m1 = MATRIX_FN(new)(10, 10);

    MATRIX_TYPE data[] = {1, 2, 3, 4, 5};

    MAT_FN(setrow)(m1, 2, 3, data, 5);
    MAT_FN(setrow)(m1, 0, 0, data, 3);
    MAT_FN(setrow)(m1, 9, 0, data, 4);

    // MATRIX_FN(print)(m1);

}

void t_mat_setcol() {

    MATRIX_T *m1 = MATRIX_FN(new)(10, 10);

    MATRIX_TYPE data[] = {1, 2, 3, 4, 5};

    MAT_FN(setcol)(m1, 2, 3, data, 5);
    MAT_FN(setcol)(m1, 0, 0, data, 3);

    // MATRIX_FN(print)(m1);


}

void t_matrix_set_row() {

    ejovo_seed();

    MATRIX_T *m1 = MATRIX_FN(new)(10, 10);
    MATRIX_T *row = MATRIX_FN(rand)(1, 10);

    assert(MATRIX_FN(set_row)(m1, 2, row) == EXIT_SUCCESS);

    // MATRIX_FN(print)(m1);

    printf("t_MATRIX_FN(set_row) passed\n");

}
void t_matrix_set_col() {

    ejovo_seed();

    MATRIX_T *m1 = MATRIX_FN(new)(10, 10);
    MATRIX_T *col = MATRIX_FN(rand)(10, 1);

    assert(MATRIX_FN(set_col)(m1, 2, col) == EXIT_SUCCESS);

    // MATRIX_FN(print)(m1);

    printf("t_MATRIX_FN(set_col) passed\n");

}

void t_matrix_get_col() {

    ejovo_seed();

    MATRIX_T *m1 = MATRIX_FN(rand)(10, 10);
    MATRIX_T *col = MATRIX_FN(get_col)(m1, 3);
    MATRIX_T *null = MATRIX_FN(get_col)(m1, -2);
    MATRIX_T *null_2 = MATRIX_FN(get_col)(m1, 12);

    assert(col);
    assert(!null);
    assert(!null_2);

    MATRIX_FN(print)(m1);

    MATRIX_FN(print)(col);

}

void t_matrix_get_row() {
    ejovo_seed();

    MATRIX_T *m1 = MATRIX_FN(rand)(10, 10);
    MATRIX_T *row = MATRIX_FN(get_row)(m1, 7);
    MATRIX_T *row2 = MATRIX_FN(get_row)(m1, 2);

    MATRIX_T *null = MATRIX_FN(get_row)(m1, -13);
    MATRIX_T *null2 = MATRIX_FN(get_row)(m1, 10);

    // check that the values in row and row2 are the actual values in each row
    assert(row);
    assert(row2);
    assert(!null);
    assert(!null2);

    MATRIX_FN(print)(m1);
    MATRIX_FN(print)(row);
    MATRIX_FN(print)(row2);
}

void t_matrix_times_vec() {
    ejovo_seed();

    MATRIX_T *m1 = MATRIX_FN(random)(5, 4, 0, 3);
    MATRIX_T *col = MATRIX_FN(random)(4, 1, 0, 10);
    MATRIX_T *row = MATRIX_FN(random)(1, 5, -5, 5);

    MATRIX_T *m2 = MATRIX_FN(multiply)(m1, col);
    MATRIX_T *m3 = MATRIX_FN(multiply)(row, m1);

    MATRIX_FN(print)(m1);
    MATRIX_FN(print)(col);
    MATRIX_FN(print)(m2);

    printf("\n\n");

    MATRIX_FN(print)(row);
    MATRIX_FN(print)(m1);
    MATRIX_FN(print)(m3);

}

void t_matrix_scalar() {

    MATRIX_T *m = MATRIX_FN(random)(10, 20, 0, 5);
    MATRIX_T *m2 = MATRIX_FN(mult_scalar)(m, 10);
    MATRIX_T *m3 = MATRIX_FN(add_scalar)(m2, 50);
    MATRIX_T *m4 = MATRIX_FN(div_scalar)(m3, 5);
    MATRIX_T *m5 = MATRIX_FN(sub_scalar)(m4, 20);

    MATRIX_FN(print)(m);
    MATRIX_FN(print)(m2);
    MATRIX_FN(print)(m3);
    MATRIX_FN(print)(m4);
    MATRIX_FN(print)(m5);

}

void t_matrix_matrix() {

    MATRIX_T *m = MATRIX_FN(random)(5, 10, 0, 3);
    MATRIX_T *m1 = MATRIX_FN(random)(5, 10, 0, 10);

    MATRIX_FN(print)(m);
    MATRIX_FN(print)(m1);

    MAT_FN(mult_foreach)(m, m1);

    MATRIX_FN(print)(m);

}

void t_vecnorm() {

    MATRIX_T *m = MATRIX_FN(rand)(8, 1);

    MATRIX_FN(print)(m);

    vecnormalize(m);

    MATRIX_FN(print)(m);

}

void t_vector_normalize() {

    MATRIX_T *m = MATRIX_FN(rand)(12, 3);
    MATRIX_T *n = VECTOR_FN(normalize)(m);

    MATRIX_FN(print)(m);
    MATRIX_FN(print)(n);




}

void t_vector_inner() {

    MATRIX_T *m = MATRIX_FN(random)(5, 1, 0, 10);
    MATRIX_T *m2 = MATRIX_FN(random)(5, 1, 0, 5);

    MATRIX_FN(print)(m);
    MATRIX_FN(print)(m2);

    printf("inner product: %lf\n", VECTOR_FN(inner)(m, m2));




}

// void t_ColIter() {

//     MATRIX_T *m = MATRIX_FN(rand)(5, 10);

//     ColIter *c = MATRIX_FN(col_begin)(m, 2); // initialize a new column iterator starting at the beginning of column 3
//     ColIter *end = MATRIX_FN(col_end)(m, 2);

//     MATRIX_FN(print)(m);

//     // printf("Element at start: %lf\n", *(c->ptr));
//     // printf("Element at end:   %lf\n", *(end->ptr));


//     do {
//         // do some thing
//         printf("Element at ColIter: %lf\n", *(c->ptr));
//         ColIter_next(c);
//     }
//     while (!ColIter_cmp(c, end));

// }

void t_mat_normcols() {

    MATRIX_T *m = MATRIX_FN(random)(15, 10, 0, 51);

    MATRIX_FN(print)(m);

    printf("MATRIX_FN(col_norm)(m, 3): %lf\n", MATRIX_FN(col_norm)(m, 3));

    MATRIX_FN(normalize_cols)(m);
    MATRIX_FN(print)(m);

}

void times_3(MATRIX_TYPE *__a) {
    *(__a) *= 3;
}


void t_matrix_foreach() {

    MATRIX_T *m = MATRIX_FN(value)(3, 3, 5);
    MATRIX_FN(print)(m);

    MATRIX_FN(foreach)(m, times_3);
    MATRIX_FN(print)(m);

    MATRIX_FN(free)(m);


}

bool gt_50(MATRIX_TYPE *__a) {
    return *(__a) > 50;
}

void t_matrix_mask() {

    MATRIX_T *m = MATRIX_FN(rand)(10, 10);
    MATRIX_FN(print)(m);

    MATRIX_FN(fill_mask)(m, gt_50, 0);
    MATRIX_FN(print)(m);

    MATRIX_FN(free)(m);

}

void t_matrix_pow() {

    MATRIX_T *m = MATRIX_FN(identity)(4);
    MATRIX_FN(print)(m);
}