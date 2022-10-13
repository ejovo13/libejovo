#include "ejovo_matrix_generic.h"
#include <assert.h>
#include "ejovo_assert.h"
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

    Matrix_d *m1 = matalloc_d(10, 15);
    Matrix_d *m2 = matalloc_d(1000, 50);
    Matrix_d *m3 = matalloc_d(10000, 10000);

    assert(m1);
    assert(m2);
    assert(m3);

    assert(m1->nrows == 10 && m1->ncols == 15);
    assert(m2->nrows == 1000 && m2->ncols == 50);
    assert(m3->nrows == 10000 && m3->ncols == 10000);

    Matrix_free_d(m1);
    Matrix_free_d(m2);
    Matrix_free_d(m3);
    printf("t_matalloc passed\n");

}

// Verify allocations with Matrix_new_d
void t_matrix_new() {

    Matrix_d *m1 = Matrix_new_d(10, 15);
    Matrix_d *m2 = Matrix_new_d(1000, 50);
    Matrix_d *m3 = Matrix_new_d(10000, 10000);

    Matrix_d *m4 = Matrix_new_d(-10, -10);

    assert(m1);
    assert(m2);
    assert(m3);
    assert(m4);

    assert(m1->nrows == 10 && m1->ncols == 15);
    assert(m2->nrows == 1000 && m2->ncols == 50);
    assert(m3->nrows == 10000 && m3->ncols == 10000);

    assert(m4->nrows == 0 && m4->ncols == 0);

    Matrix_free_d(m1);
    Matrix_free_d(m2);
    Matrix_free_d(m3);
    Matrix_free_d(m4);

    printf("t_Matrix_new_d passed\n");
}

void t_matrix_move() {

    double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double *arr_ptr = (double *) arr;
    double arr_copy[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // ARR_PTR HAS BEEN NULLIFIED!!!!!!!!!
    printf("Address of arr_ptr before call: %p\n", arr_ptr);
    printf("Address of arr before call: %p\n", arr);
    Matrix_d *m = Matrix_move_d(&arr_ptr, 3, 3); // moving a local variable, if m
                                         // persists out side of this call, it is dead
    // Matrix_d *m1 = Matrix_move_d(arr, 1, 9); // THIS IS SUPER DANGEROUS, THESE TWO ARRAYS
                                             // ARE POINTING TO THE SAME BLOCK OF DATA
                                             // PREFER TO USE MATRIX_CLONE_ARRAY


    printf("Address of arr_ptr: %p\n", arr_ptr);
    printf("Address of m->data: %p\n", m->data);
    // ASSERT THAT ARR_PTR IS NULL
    rassert(!arr_ptr);


    // Verify that the two matrices are identical (and are using the same data)
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            rassert(matat_d(m, i, j) == arr_copy[i * 3 + j]);
            // assert(matacc_d(m, i, j) == matacc_d(m1, 0, i * 3 + j)); // Verify that the pointers are in fact identical
        }
    }

    printf("t_Matrix_from_arr_d passed\n");

}

void t_matrix_from() {

    double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Matrix_d *m = Matrix_from_d(arr, 3, 3);
    Matrix_d *m1 = Matrix_from_d(arr, 1, 9); // This time were are creating a new copy
                                              // and the resources are not shared

    Matrix_set_d(m1, 0, 3, -50);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {

            if (i == 1 && j == 0) {
                rassert(Matrix_at_d(m, i, j) == arr[i * 3 + j]);
                rassert(Matrix_at_d(m1, 0, i * 3 + j) != arr[i * 3 + j]); // we modified m1 so make sure that it is different
                rassert(Matrix_access_d(m, i, j) != Matrix_access_d(m1, 0, i * 3 + j)); // make sure the pointes are different.
            } else {

                rassert(Matrix_at_d(m, i, j) == arr[i * 3 + j]);
                rassert(Matrix_at_d(m1, 0, i * 3 + j) == arr[i * 3 + j]); // we modified m1 so make sure that it is different
                rassert(Matrix_access_d(m, i, j) != Matrix_access_d(m1, 0, i * 3 + j)); // make sure the pointes are different.

            }
        }
    }

    printf("t_Matrix_clone_arr_d passed\n");
}

void t_matrix_colvec() {

    double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Matrix_d *m = Matrix_colvec_d(arr, 9);

    assert(m);

    // Matrix_print_d(m);

    Matrix_free_d(m);

}

void t_matrix_rowvec() {

    double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Matrix_d *m = Matrix_rowvec_d(arr, 9);

    assert(m);

    // Matrix_print_d(m);

    Matrix_free_d(m);
}



// Bounds are 0-indexed
void t_matrix_valid_bounds() {

    Matrix_d *m1 = Matrix_new_d(50, 25);

    rassert(Matrix_valid_bounds_d(m1, 0, 0));
    rassert(Matrix_valid_bounds_d(m1, 10, 10));
    rassert(Matrix_valid_bounds_d(m1, 30, 10));
    rassert(Matrix_valid_bounds_d(m1, 49, 10));
    rassert(Matrix_valid_bounds_d(m1, 23, 24));
    rassert(Matrix_valid_bounds_d(m1, 49, 24));

    rassert(!Matrix_valid_bounds_d(m1, 10, 30));
    rassert(!Matrix_valid_bounds_d(m1, 50, 10));
    rassert(!Matrix_valid_bounds_d(m1, 49, 25));
    rassert(!Matrix_valid_bounds_d(m1, -3, 13));

    printf("t_Matrix_valid_bounds_d passed\n");
}

// If out of bounds return -1
void t_matrix_at() {

    Matrix_d *m1 = Matrix_new_d(10, 10);

    for (size_t i = 0; i < m1->nrows; i++) {
        for (size_t j = 0; j < m1->ncols; j++) {

            assert(Matrix_at_d(m1, i, j) == 0);
            assert(matat_d(m1, i, j) == 0);
        }
    }

    assert(Matrix_at_d(m1, 0, -3) == -1); // this will warn stderr that we are trying to access an unacceptable bound

    Matrix_free_d(m1);
    printf("t_Matrix_valid_bounds_d passed\n");
}

void t_matrix_set() {

    Matrix_d *m1 = Matrix_new_d(3, 3);
    Matrix_d *m2 = Matrix_new_d(3, 3);

    double arr[] = {1, 2, 3, 56, 7, 45, 23, 76, 23};
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            Matrix_set_d(m1, i, j, arr[i * 3 + j]);
            matset_d(m2, i, j, arr[i * 3 + j]);
        }
    }

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            assert(Matrix_at_d(m1, i, j) == arr[i * 3 + j]);
            assert(matat_d(m2, i, j) == arr[i * 3 + j]);
        }
    }

    Matrix_free_d(m1);
    Matrix_free_d(m2);

    printf("t_Matrix_set_d passed\n");

}

void t_matrix_access() {

    Matrix_d *m1 = Matrix_new_d(15, 15);

    Matrix_set_d(m1, 13, 4, 1.0);

    double *el_ptr = Matrix_access_d(m1, 13, 4);
    double *el_ptr_nocheck = matacc_d(m1, 13, 4);

    rassert(el_ptr == el_ptr_nocheck);
    rassert(*el_ptr == 1.0);

    el_ptr = Matrix_access_d(m1, 15, 15);
    assert(!el_ptr); // make sure that upon a bad access request el_ptr returns null

    Matrix_free_d(m1);

    printf("t_Matrix_access_d passed\n");

}

// Requires manual inspection
void t_matrix_print() {

    Matrix_d *m1 = Matrix_new_d(5, 13);
    Matrix_print_d(m1);

    assert(true);
    Matrix_free_d(m1);

}

// void t_mat_cdr() {

//     double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//     double data2[] = {4, 2, 5, 1, 9, 8, 3, 2, 1, 2, 4, 5};


//     Matrix_d *m1 = Matrix_from_d(data, 3, 3);
//     Matrix_d *m2 = Matrix_from_d(data2, 3, 3);

    // TODO implement test

// }

void t_mat_setrow() {

    Matrix_d *m1 = Matrix_new_d(10, 10);

    double data[] = {1, 2, 3, 4, 5};

    matsetrow_d(m1, 2, 3, data, 5);
    matsetrow_d(m1, 0, 0, data, 3);
    matsetrow_d(m1, 9, 0, data, 4);

    // Matrix_print_d(m1);

}

void t_mat_setcol() {

    Matrix_d *m1 = Matrix_new_d(10, 10);

    double data[] = {1, 2, 3, 4, 5};

    matsetcol_d(m1, 2, 3, data, 5);
    matsetcol_d(m1, 0, 0, data, 3);

    // Matrix_print_d(m1);


}

void t_matrix_set_row() {

    ejovo_seed();

    Matrix_d *m1 = Matrix_new_d(10, 10);
    Matrix_d *row = Matrix_rand_d(1, 10);

    rassert(Matrix_set_row_d(m1, 2, row) == EXIT_SUCCESS);

    // Matrix_print_d(m1);

    printf("t_Matrix_set_row_d passed\n");

}
void t_matrix_set_col() {

    ejovo_seed();

    Matrix_d *m1 = Matrix_new_d(10, 10);
    Matrix_d *col = Matrix_rand_d(10, 1);

    rassert(Matrix_set_col_d(m1, 2, col) == EXIT_SUCCESS);

    // Matrix_print_d(m1);

    printf("t_Matrix_set_col_d passed\n");

}

void t_matrix_get_col() {

    ejovo_seed();

    Matrix_d *m1 = Matrix_rand_d(10, 10);
    Matrix_d *col = Matrix_get_col_d(m1, 3);
    Matrix_d *null = Matrix_get_col_d(m1, -2);
    Matrix_d *null_2 = Matrix_get_col_d(m1, 12);

    rassert(col);
    rassert(!null);
    rassert(!null_2);

    Matrix_print_d(m1);

    Matrix_print_d(col);

}

void t_matrix_get_row() {
    ejovo_seed();

    Matrix_d *m1 = Matrix_rand_d(10, 10);
    Matrix_d *row = Matrix_get_row_d(m1, 7);
    Matrix_d *row2 = Matrix_get_row_d(m1, 2);

    Matrix_d *null = Matrix_get_row_d(m1, -13);
    Matrix_d *null2 = Matrix_get_row_d(m1, 10);

    // check that the values in row and row2 are the actual values in each row
    rassert(row);
    rassert(row2);
    rassert(!null);
    rassert(!null2);

    Matrix_print_d(m1);
    Matrix_print_d(row);
    Matrix_print_d(row2);

    Matrix_free_d(m1);
    Matrix_free_d(row);
    Matrix_free_d(row2);

}

void t_matrix_times_vec() {
    ejovo_seed();

    Matrix_d *m1 = Matrix_random_d(5, 4, 0, 3);
    Matrix_d *col = Matrix_random_d(4, 1, 0, 10);
    Matrix_d *row = Matrix_random_d(1, 5, -5, 5);

    Matrix_d *m2 = Matrix_multiply_d(m1, col);
    Matrix_d *m3 = Matrix_multiply_d(row, m1);

    Matrix_print_d(m1);
    Matrix_print_d(col);
    Matrix_print_d(m2);

    printf("\n\n");

    Matrix_print_d(row);
    Matrix_print_d(m1);
    Matrix_print_d(m3);

}

void t_matrix_scalar() {

    Matrix_d *m = Matrix_random_d(10, 20, 0, 5);
    Matrix_d *m2 = Matrix_mult_scalar_d(m, 10);
    Matrix_d *m3 = Matrix_add_scalar_d(m2, 50);
    Matrix_d *m4 = Matrix_div_scalar_d(m3, 5);
    Matrix_d *m5 = Matrix_sub_scalar_d(m4, 20);

    Matrix_print_d(m);
    Matrix_print_d(m2);
    Matrix_print_d(m3);
    Matrix_print_d(m4);
    Matrix_print_d(m5);

}

void t_matrix_matrix() {

    Matrix_d *m = Matrix_random_d(5, 10, 0, 3);
    Matrix_d *m1 = Matrix_random_d(5, 10, 0, 10);

    Matrix_print_d(m);
    Matrix_print_d(m1);

    matmult_foreach_d(m, m1);

    Matrix_print_d(m);

}

void t_vecnorm() {

    Matrix_d *m = Matrix_rand_d(8, 1);

    Matrix_print_d(m);

    vecnormalize_d(m);

    Matrix_print_d(m);

}

void t_vector_normalize() {

    Matrix_d *m = Matrix_rand_d(12, 3);
    Matrix_d *n = Vector_normalize_d(m);

    Matrix_print_d(m);
    Matrix_print_d(n);




}

void t_vector_inner() {

    Matrix_d *m = Matrix_random_d(5, 1, 0, 10);
    Matrix_d *m2 = Matrix_random_d(5, 1, 0, 5);

    Matrix_print_d(m);
    Matrix_print_d(m2);

    printf("inner product: %lf\n", Vector_inner_d(m, m2));




}

// void t_ColIter() {

//     Matrix_d *m = Matrix_rand_d(5, 10);

//     ColIter *c = Matrix_col_begin_d(m, 2); // initialize a new column iterator starting at the beginning of column 3
//     ColIter *end = Matrix_col_end_d(m, 2);

//     Matrix_print_d(m);

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

    Matrix_d *m = Matrix_random_d(15, 10, 0, 51);

    Matrix_print_d(m);

    printf("Matrix_col_norm_d(m, 3): %lf\n", Matrix_col_norm_d(m, 3));

    Matrix_normalize_cols_d(m);
    Matrix_print_d(m);

}

void times_3(double *__a) {
    *(__a) *= 3;
}


void t_matrix_foreach() {

    Matrix_d *m = Matrix_value_d(3, 3, 5);
    Matrix_print_d(m);

    Matrix_foreach_d(m, times_3);
    Matrix_print_d(m);

    Matrix_free_d(m);


}

bool gt_50(double *__a) {
    return *(__a) > 50;
}

void t_matrix_mask() {

    Matrix_d *m = Matrix_rand_d(10, 10);
    Matrix_print_d(m);

    Matrix_fill_mask_d(m, gt_50, 0);
    Matrix_print_d(m);

    Matrix_free_d(m);

}

void t_matrix_pow() {

    Matrix_d *m = Matrix_identity_d(4);
    Matrix_print_d(m);
}