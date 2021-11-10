// test out these bad ass fucking iterator functions!!!

// I will also eventually want to benchmark these different function types

#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

void t_ColIter_ctors();
void t_ColIter_basic_utility();
void t_ColIter_basic_utility_cols();
/* TODO

    - [x] ColIter basic utility for columns (finish!!)
    - [ ] ColIter apply functions
    - [ ] ColIter column manipulations

    - [ ] All row iterator operations

*/

int main() {

    ejovo_seed();

    t_ColIter_ctors();
    t_ColIter_basic_utility();
    t_ColIter_basic_utility_cols();


    // Matrix *m = Matrix_random(5, 5, 0, 10);

    // printf("Starting matrix\n");
    // Matrix_print(m);

    // // test out the various array functions!

    // RowIter *r0begin = Matrix_row_begin(m, 0);
    // RowIter *r0col9 = matrowpos(m, 0, 9);

    // printf("Adding 10 to m(1,:)\n");
    // RowIter_apply_add_k(r0begin, r0col9, 10);

    // RowIter *r0end = Matrix_row_end(m, 0);
    // r0begin = matrowpos(m, 0, 3);

    // printf("Multiplying m(1,4:) by 0\n");
    // RowIter_apply_mult_k(r0begin, r0end, 0);

    // // r0begin = matrowpos(m, 0, 0);
    // RowIter *r2begin = Matrix_row_begin(m, 2);
    // RowIter *r2end = Matrix_row_end(m, 2);

    // printf("Subracting 100 from m(3,:)\n");
    // RowIter_apply_sub_k(r2begin, r2end, 100);

    // Matrix_print(m);

    // RowIter *r5begin = Matrix_row_begin(m, 4);
    // RowIter *r5end = Matrix_row_end(m, 4);

    // printf("Dividing row 5 by 5\n");
    // RowIter_apply_div_k(r5begin, r5end, 5);

    // Matrix_print(m);

    // printf("Matrix_at(0, 0) %lf\n", Matrix_at(m, 0, 0));
    // printf("Matrix_at(4, 4) %lf\n", Matrix_at(m, 4, 4));


    // printf("Adding row 3 to row 1\n");

    // RowIter *r1begin = Matrix_row_begin(m, 0);
    // RowIter *r1end = Matrix_row_end(m, 0);

    // RowIter *r3begin = Matrix_row_begin(m, 3);

    // RowIter_apply_add_iter(r1begin, r1end, r3begin);

    // Matrix_print(m);


    return 0;
}

// Test that Column iterators are created appropriately
void t_ColIter_ctors() {

    MATRIX_TYPE dub = 100;
    MATRIX_TYPE dub_arr[] = {1, 2, 3, 4, 5};

    /**======================
     *!    Single Value testing
     *========================**/
    ColIter *c = ColIter_new(&dub, 1); // nrows should be replaced with ptr_diff!!!
    assert(ColIter_value(c) == 100);
    ColIter_set(c, 10);
    assert(ColIter_value(c) == 10);

    /**======================
     *!    Array ColIter testing
     *========================**/
    ColIter *arr_begin = ColIter_new(dub_arr, 1);
    ColIter *arr_end = ColIter_new(dub_arr + 5, 1); // set the ending iterator to onte past the array!

    assert(ColIter_value(arr_begin) == 1);
    ColIter_next(arr_begin);
    assert(ColIter_value(arr_begin) == 2);
    ColIter_next(arr_begin);
    assert(ColIter_value(arr_begin) == 3);
    ColIter_next(arr_begin);
    assert(ColIter_value(arr_begin) == 4);
    ColIter_next(arr_begin);
    assert(ColIter_value(arr_begin) == 5);
    ColIter_next(arr_begin);
    assert(ColIter_cmp(arr_begin, arr_end)); // Check that the iterator now points to after the final element!

    MATRIX_TYPE data[] = {1, 2, 3, 4, 5, 6}; // row major order


    /**======================
     *!    Matrix ColIter testing
     *========================**/
    Matrix *m = Matrix_from(data, 3, 2); // create a new matrix from the data provided

    ColIter *c0 = Matrix_col_begin(m, 0);
    ColIter *c0_clone = ColIter_clone(c0);
    ColIter *c1 = Matrix_col_begin(m, 1);

    const ColIter *c0_end = Matrix_col_end(m, 0);
    const ColIter *c1_end = Matrix_col_end(m, 1);

    assert(ColIter_value(c0) == 1);
    assert(ColIter_value(c0_clone) == 1);
    assert(ColIter_value(c1) == 2);
    assert(ColIter_cmp(c0, matcolpos(m, 0, 0))); // check that matcolpos returns the approprate results
    assert(ColIter_cmp(c1, matcolpos(m, 0, 1)));
    // iterate
    ColIter_next(c0);
    ColIter_next(c0_clone);
    ColIter_next(c1);

    assert(ColIter_value(c0) == 3);
    assert(ColIter_value(c0_clone) == 3);
    assert(ColIter_value(c1) == 4);
    assert(ColIter_cmp(c0, matcolpos(m, 1, 0)));
    assert(ColIter_cmp(c1, matcolpos(m, 1, 1)));

    ColIter_next(c0);
    ColIter_next(c0_clone);
    ColIter_next(c1);

    assert(ColIter_value(c0) == 5);
    assert(ColIter_value(c0_clone) == 5);
    assert(ColIter_value(c1) == 6);
    assert(ColIter_cmp(c0, matcolpos(m, 2, 0)));
    assert(ColIter_cmp(c1, matcolpos(m, 2, 1)));

    ColIter_next(c0);
    ColIter_next(c0_clone);
    ColIter_next(c1);

    assert(ColIter_cmp(c0, c0_end));
    assert(ColIter_cmp(c0_clone, c0_end));
    assert(ColIter_cmp(c1, c1_end));
    assert(ColIter_cmp(c0, matcolpos(m, 3, 0)));
    assert(ColIter_cmp(c1, matcolpos(m, 3, 1)));

    printf("ColIter_ctors passed\n");

}

// Test the functions defined under the "Basic utility" heading
void t_ColIter_basic_utility() {

    Matrix *m = Matrix_new(4, 4); // create a matrix of zeros

    ColIter *c0 = Matrix_col_begin(m, 0);

    /**======================
     *!    WARNING HEADER
    *========================**/
    ColIter_set(c0, 10);
    assert(Matrix_at(m, 0, 0) == 10);

    ColIter_next(c0);
    ColIter_add_k(c0, 51.3);
    assert(Matrix_at(m, 1, 0) == 51.3);

    ColIter_next(c0);
    ColIter_sub_k(c0, 13.9);
    assert(Matrix_at(m, 2, 0) == -13.9);
    ColIter_mult_k(c0, 2);
    assert(Matrix_at(m, 2, 0) == -13.9 * 2);
    ColIter_div_k(c0, 4);
    assert(Matrix_at(m, 2, 0) == -13.9 / 2);

    /**======================
     *!    Ptr operations
     *========================**/
    MATRIX_TYPE v1 = 13;
    MATRIX_TYPE v2 = 3;
    MATRIX_TYPE v3 = 1934.2;
    MATRIX_TYPE v4 = 145.3;
    MATRIX_TYPE v5 = 152;

    ColIter *c1 = Matrix_col_begin(m, 1);

    ColIter_set_ptr(c1, &v1);
    assert(Matrix_at(m, 0, 1) == v1);

    ColIter_next(c1);
    ColIter_add_ptr(c1, &v2);
    assert(Matrix_at(m, 1, 1) == v2);

    ColIter_next(c1);
    ColIter_sub_ptr(c1, &v3);
    assert(Matrix_at(m, 2, 1) == -v3);
    ColIter_mult_ptr(c1, &v4);
    assert(Matrix_at(m, 2, 1) == -v3 * v4);
    ColIter_div_ptr(c1, &v5);
    assert(Matrix_at(m, 2, 1) == (-v3 * v4) / v5);

    /**======================
     *!    Iterator operations
     *========================**/
    c1 = Matrix_col_begin(m, 1); // reset the iterator
    ColIter *c2 = Matrix_col_begin(m, 2);

    ColIter_set_iter(c2, c1); // Set the 3rd column first row equal to v1
    assert(Matrix_at(m, 0, 2) == v1);

    ColIter_next(c2);
    ColIter_add_iter(c2, c1); // Add v1 to 0
    ColIter_next(c1); // advance c1 to the second row
    ColIter_sub_iter(c2, c1); // subtract v2
    assert(Matrix_at(m, 1, 2) == v1 - v2);

    ColIter_next(c2);
    ColIter_next(c1); // advance c1 to the third row, (-v3 * v4)

    ColIter_set(c2, 10);
    ColIter_mult_iter(c2, c1);
    assert(Matrix_at(m, 2, 2) == (10 * ((-v3 * v4) / v5)));
    ColIter_div_iter(c2, c2);
    assert(Matrix_at(m, 2, 2) == 1);

    printf("Basic utility passed\n");

}

void t_ColIter_basic_utility_cols() {

    Matrix *m = Matrix_new(10, 10);

    ColIter *c0 = Matrix_col_begin(m, 0);
    ColIter *c1 = Matrix_col_begin(m, 1);
    ColIter *c2 = Matrix_col_begin(m, 2);
    ColIter *c3 = Matrix_col_begin(m, 3);
    ColIter *c4 = Matrix_col_begin(m, 4);
    ColIter *c5 = Matrix_col_begin(m, 5);
    const ColIter *c0_end = Matrix_col_end(m, 0);
    const ColIter *c1_end = Matrix_col_end(m, 1);
    const ColIter *c2_end = Matrix_col_end(m, 2);
    const ColIter *c3_end = Matrix_col_end(m, 3);
    const ColIter *c4_end = Matrix_col_end(m, 4);
    const ColIter *c5_end = Matrix_col_end(m, 5);

    ColIter_col_set_k(c0, c0_end, 10);
    ColIter_col_add_k(c1, c1_end, 5);
    ColIter_col_sub_k(c2, c2_end, 13);
    ColIter_col_div_k(c0, c0_end, 5);
    ColIter_col_mult_k(c1, c1_end, 3);
    ColIter_col_add_col(c3, c3_end, c0);

    for (size_t i = 0; i < 10; i++) {
        assert(Matrix_at(m, i, 0) == 10 / 5);
        assert(Matrix_at(m, i, 1) == 5 * 3);
        assert(Matrix_at(m, i, 2) == -13);
        assert(Matrix_at(m, i, 3) == Matrix_at(m, i, 0));
    }

    // Matrix_print(m);
    printf("Basic utility cols passed \n");

}