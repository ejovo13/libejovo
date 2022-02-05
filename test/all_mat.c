#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

void t_matalloc();
void t_Matrix_new();
void t_Matrix_move();
void t_Matrix_from();
void t_Matrix_colvec();
void t_Matrix_rowvec();
void t_Matrix_valid_bounds();
void t_Matrix_at();
void t_Matrix_access();
void t_Matrix_print();
void t_matsetcol();
void t_matsetrow();
void t_Matrix_set_row();
void t_Matrix_set_col();
void t_Matrix_get_row();
void t_Matrix_get_col();
void t_Matrix_times_vec();

void t_Matrix_foreach();

void t_Matrix_scalar();
void t_Matrix_matrix();
void t_vecnorm();
void t_Vector_normalize();
void t_Vector_inner();
void t_ColIter();
void t_matnormcols();

void t_Matrix_mask();
void t_Matrix_pow();


int main() {

    t_matalloc();
    t_Matrix_new();
    t_Matrix_move();
    t_Matrix_from();
    t_Matrix_colvec();
    t_Matrix_rowvec();
    t_Matrix_valid_bounds();
    t_Matrix_at();
    t_Matrix_access();
    t_Matrix_print();
    t_matsetrow();
    t_matsetcol();
    t_Matrix_set_row();
    t_Matrix_set_col();
    t_Matrix_get_row();
    t_Matrix_get_col();
    t_Matrix_times_vec();

    t_Matrix_foreach();

    t_Matrix_scalar();
    t_Matrix_matrix();
    t_vecnorm();
    t_Vector_normalize();
    t_Vector_inner();
    // t_ColIter();
    t_matnormcols();

    t_Matrix_mask();
    t_Matrix_pow();



    return 0;
}

// verify that allocating various sizes of a matrix doesn't lead to a malloc error
void t_matalloc() {

    Matrix *m1 = matalloc(10, 15);
    Matrix *m2 = matalloc(1000, 50);
    Matrix *m3 = matalloc(10000, 10000);

    assert(m1);
    assert(m2);
    assert(m3);

    assert(m1->nrows == 10 && m1->ncols == 15);
    assert(m2->nrows == 1000 && m2->ncols == 50);
    assert(m3->nrows == 10000 && m3->ncols == 10000);

    Matrix_free(m1);
    Matrix_free(m2);
    Matrix_free(m3);
    printf("t_matalloc passed\n");

}

// Verify allocations with Matrix_new
void t_Matrix_new() {

    Matrix *m1 = Matrix_new(10, 15);
    Matrix *m2 = Matrix_new(1000, 50);
    Matrix *m3 = Matrix_new(10000, 10000);

    Matrix *m4 = Matrix_new(-10, -10);

    assert(m1);
    assert(m2);
    assert(m3);
    assert(m4);

    assert(m1->nrows == 10 && m1->ncols == 15);
    assert(m2->nrows == 1000 && m2->ncols == 50);
    assert(m3->nrows == 10000 && m3->ncols == 10000);

    assert(m4->nrows == 0 && m4->ncols == 0);

    Matrix_free(m1);
    Matrix_free(m2);
    Matrix_free(m3);
    Matrix_free(m4);

    printf("t_Matrix_new passed\n");
}

void t_Matrix_move() {

    MATRIX_TYPE arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    MATRIX_TYPE *arr_ptr = (MATRIX_TYPE *) arr;
    MATRIX_TYPE arr_copy[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // ARR_PTR HAS BEEN NULLIFIED!!!!!!!!!
    printf("Address of arr_ptr before call: %p\n", arr_ptr);
    printf("Address of arr before call: %p\n", arr);
    Matrix *m = Matrix_move(&arr_ptr, 3, 3); // moving a local variable, if m
                                         // persists out side of this call, it is dead
    // Matrix *m1 = Matrix_move(arr, 1, 9); // THIS IS SUPER DANGEROUS, THESE TWO ARRAYS
                                             // ARE POINTING TO THE SAME BLOCK OF DATA
                                             // PREFER TO USE MATRIX_CLONE_ARRAY


    printf("Address of arr_ptr: %p\n", arr_ptr);
    printf("Address of m->data: %p\n", m->data);
    // ASSERT THAT ARR_PTR IS NULL
    assert(!arr_ptr);


    // Verify that the two matrices are identical (and are using the same data)
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            assert(matat(m, i, j) == arr_copy[i * 3 + j]);
            // assert(matacc(m, i, j) == matacc(m1, 0, i * 3 + j)); // Verify that the pointers are in fact identical
        }
    }

    printf("t_Matrix_from_arr passed\n");

}

void t_Matrix_from() {

    MATRIX_TYPE arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Matrix *m = Matrix_from(arr, 3, 3);
    Matrix *m1 = Matrix_from(arr, 1, 9); // This time were are creating a new copy
                                              // and the resources are not shared

    Matrix_set(m1, 0, 3, -50);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {

            if (i == 1 && j == 0) {
                assert(Matrix_at(m, i, j) == arr[i * 3 + j]);
                assert(Matrix_at(m1, 0, i * 3 + j) != arr[i * 3 + j]); // we modified m1 so make sure that it is different
                assert(Matrix_access(m, i, j) != Matrix_access(m1, 0, i * 3 + j)); // make sure the pointes are different.
            } else {

                assert(Matrix_at(m, i, j) == arr[i * 3 + j]);
                assert(Matrix_at(m1, 0, i * 3 + j) == arr[i * 3 + j]); // we modified m1 so make sure that it is different
                assert(Matrix_access(m, i, j) != Matrix_access(m1, 0, i * 3 + j)); // make sure the pointes are different.

            }
        }
    }

    printf("t_Matrix_clone_arr passed\n");
}

void t_Matrix_colvec() {

    MATRIX_TYPE arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Matrix *m = Matrix_colvec(arr, 9);

    assert(m);

    // Matrix_print(m);

    Matrix_free(m);

}

void t_Matrix_rowvec() {

    MATRIX_TYPE arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Matrix *m = Matrix_rowvec(arr, 9);

    assert(m);

    // Matrix_print(m);

    Matrix_free(m);
}



// Bounds are 0-indexed
void t_Matrix_valid_bounds() {

    Matrix *m1 = Matrix_new(50, 25);

    assert(Matrix_valid_bounds(m1, 0, 0));
    assert(Matrix_valid_bounds(m1, 10, 10));
    assert(Matrix_valid_bounds(m1, 30, 10));
    assert(Matrix_valid_bounds(m1, 49, 10));
    assert(Matrix_valid_bounds(m1, 23, 24));
    assert(Matrix_valid_bounds(m1, 49, 24));

    assert(!Matrix_valid_bounds(m1, 10, 30));
    assert(!Matrix_valid_bounds(m1, 50, 10));
    assert(!Matrix_valid_bounds(m1, 49, 25));
    assert(!Matrix_valid_bounds(m1, -3, 13));

    printf("t_Matrix_valid_bounds passed\n");
}

// If out of bounds return -1
void t_Matrix_at() {

    Matrix *m1 = Matrix_new(10, 10);

    for (size_t i = 0; i < m1->nrows; i++) {
        for (size_t j = 0; j < m1->ncols; j++) {

            assert(Matrix_at(m1, i, j) == 0);
            assert(matat(m1, i, j) == 0);
        }
    }

    assert(Matrix_at(m1, 0, -3) == -1); // this will warn stderr that we are trying to access an unacceptable bound

    Matrix_free(m1);
    printf("t_Matrix_valid_bounds passed\n");
}

void t_Matrix_set() {

    Matrix *m1 = Matrix_new(3, 3);
    Matrix *m2 = Matrix_new(3, 3);

    MATRIX_TYPE arr[] = {1, 2, 3, 56, 7, 45, 23, 76, 23};
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            Matrix_set(m1, i, j, arr[i * 3 + j]);
            matset(m2, i, j, arr[i * 3 + j]);
        }
    }

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            assert(Matrix_at(m1, i, j) == arr[i * 3 + j]);
            assert(matat(m2, i, j) == arr[i * 3 + j]);
        }
    }

    Matrix_free(m1);
    Matrix_free(m2);

    printf("t_Matrix_set passed\n");

}

void t_Matrix_access() {

    Matrix *m1 = Matrix_new(15, 15);

    Matrix_set(m1, 13, 4, 1.0);

    MATRIX_TYPE *el_ptr = Matrix_access(m1, 13, 4);
    MATRIX_TYPE *el_ptr_nocheck = matacc(m1, 13, 4);

    assert(el_ptr == el_ptr_nocheck);
    assert(*el_ptr == 1.0);

    el_ptr = Matrix_access(m1, 15, 15);
    assert(!el_ptr); // make sure that upon a bad access request el_ptr returns null

    Matrix_free(m1);

    printf("t_Matrix_access passed\n");

}

// Requires manual inspection
void t_Matrix_print() {

    Matrix *m1 = Matrix_new(5, 13);
    Matrix_print(m1);

    assert(true);
    Matrix_free(m1);

}

void t_matcdr() {

    MATRIX_TYPE data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    MATRIX_TYPE data2[] = {4, 2, 5, 1, 9, 8, 3, 2, 1, 2, 4, 5};


    Matrix *m1 = Matrix_from(data, 3, 3);
    Matrix *m2 = Matrix_from(data2, 3, 3);



}

void t_matsetrow() {

    Matrix *m1 = Matrix_new(10, 10);

    MATRIX_TYPE data[] = {1, 2, 3, 4, 5};

    matsetrow(m1, 2, 3, data, 5);
    matsetrow(m1, 0, 0, data, 3);
    matsetrow(m1, 9, 0, data, 4);

    // Matrix_print(m1);

}

void t_matsetcol() {

    Matrix *m1 = Matrix_new(10, 10);

    MATRIX_TYPE data[] = {1, 2, 3, 4, 5};

    matsetcol(m1, 2, 3, data, 5);
    matsetcol(m1, 0, 0, data, 3);

    // Matrix_print(m1);


}

void t_Matrix_set_row() {

    ejovo_seed();

    Matrix *m1 = Matrix_new(10, 10);
    Matrix *row = Matrix_rand(1, 10);

    assert(Matrix_set_row(m1, 2, row) == EXIT_SUCCESS);

    // Matrix_print(m1);

    printf("t_Matrix_set_row passed\n");

}
void t_Matrix_set_col() {

    ejovo_seed();

    Matrix *m1 = Matrix_new(10, 10);
    Matrix *col = Matrix_rand(10, 1);

    assert(Matrix_set_col(m1, 2, col) == EXIT_SUCCESS);

    // Matrix_print(m1);

    printf("t_Matrix_set_col passed\n");

}

void t_Matrix_get_col() {

    ejovo_seed();

    Matrix *m1 = Matrix_rand(10, 10);
    Matrix *col = Matrix_get_col(m1, 3);
    Matrix *null = Matrix_get_col(m1, -2);
    Matrix *null_2 = Matrix_get_col(m1, 12);

    assert(col);
    assert(!null);
    assert(!null_2);

    Matrix_print(m1);

    Matrix_print(col);

}

void t_Matrix_get_row() {
    ejovo_seed();

    Matrix *m1 = Matrix_rand(10, 10);
    Matrix *row = Matrix_get_row(m1, 7);
    Matrix *row2 = Matrix_get_row(m1, 2);

    Matrix *null = Matrix_get_row(m1, -13);
    Matrix *null2 = Matrix_get_row(m1, 10);

    // check that the values in row and row2 are the actual values in each row
    assert(row);
    assert(row2);
    assert(!null);
    assert(!null2);

    Matrix_print(m1);
    Matrix_print(row);
    Matrix_print(row2);
}

void t_Matrix_times_vec() {
    ejovo_seed();

    Matrix *m1 = Matrix_random(5, 4, 0, 3);
    Matrix *col = Matrix_random(4, 1, 0, 10);
    Matrix *row = Matrix_random(1, 5, -5, 5);

    Matrix *m2 = Matrix_multiply(m1, col);
    Matrix *m3 = Matrix_multiply(row, m1);

    Matrix_print(m1);
    Matrix_print(col);
    Matrix_print(m2);

    printf("\n\n");

    Matrix_print(row);
    Matrix_print(m1);
    Matrix_print(m3);

}

void t_Matrix_scalar() {

    Matrix *m = Matrix_random(10, 20, 0, 5);
    Matrix *m2 = Matrix_mult_scalar(m, 10);
    Matrix *m3 = Matrix_add_scalar(m2, 50);
    Matrix *m4 = Matrix_div_scalar(m3, 5);
    Matrix *m5 = Matrix_sub_scalar(m4, 20);

    Matrix_print(m);
    Matrix_print(m2);
    Matrix_print(m3);
    Matrix_print(m4);
    Matrix_print(m5);

}

void t_Matrix_matrix() {

    Matrix *m = Matrix_random(5, 10, 0, 3);
    Matrix *m1 = Matrix_random(5, 10, 0, 10);

    Matrix_print(m);
    Matrix_print(m1);

    matmult_foreach(m, m1);

    Matrix_print(m);

}

void t_vecnorm() {

    Matrix *m = Matrix_rand(8, 1);

    Matrix_print(m);

    vecnormalize(m);

    Matrix_print(m);

}

void t_Vector_normalize() {

    Matrix *m = Matrix_rand(12, 3);
    Matrix *n = Vector_normalize(m);

    Matrix_print(m);
    Matrix_print(n);




}

void t_Vector_inner() {

    Matrix *m = Matrix_random(5, 1, 0, 10);
    Matrix *m2 = Matrix_random(5, 1, 0, 5);

    Matrix_print(m);
    Matrix_print(m2);

    printf("inner product: %lf\n", Vector_inner(m, m2));




}

// void t_ColIter() {

//     Matrix *m = Matrix_rand(5, 10);

//     ColIter *c = Matrix_col_begin(m, 2); // initialize a new column iterator starting at the beginning of column 3
//     ColIter *end = Matrix_col_end(m, 2);

//     Matrix_print(m);

//     // printf("Element at start: %lf\n", *(c->ptr));
//     // printf("Element at end:   %lf\n", *(end->ptr));


//     do {
//         // do some thing
//         printf("Element at ColIter: %lf\n", *(c->ptr));
//         ColIter_next(c);
//     }
//     while (!ColIter_cmp(c, end));

// }

void t_matnormcols() {

    Matrix *m = Matrix_random(15, 10, 0, 51);

    Matrix_print(m);

    printf("Matrix_col_norm(m, 3): %lf\n", Matrix_col_norm(m, 3));

    Matrix_normalize_cols(m);
    Matrix_print(m);

}

void times_3(MATRIX_TYPE *__a) {
    *(__a) *= 3;
}


void t_Matrix_foreach() {

    Matrix *m = Matrix_value(3, 3, 5);
    Matrix_print(m);

    Matrix_foreach(m, times_3);
    Matrix_print(m);

    Matrix_free(m);


}

bool gt_50(MATRIX_TYPE *__a) {
    return *(__a) > 50;
}

void t_Matrix_mask() {

    Matrix *m = Matrix_rand(10, 10);
    Matrix_print(m);

    Matrix_fill_mask(m, gt_50, 0);
    Matrix_print(m);

    Matrix_free(m);

}

void t_Matrix_pow() {

    Matrix *m = Matrix_identity(4);
    Matrix_print(m);
}