// test out these bad ass fucking iterator functions!!!

// I will also eventually want to benchmark these different function types
#include "test_mat.h"

void t_iter();

void t_diag_wide();
void t_diag_tall();
void t_diag_sq();


void t_length(); /* Verify that the length calculated is accurate. */
void t_set_iter_pow();

void t_minmax();
// void t_coliter();
// void t_diagiter();

int main() {

    ejovo_seed();

    // t_iter();
    t_diag_wide();
    t_diag_tall();
    t_diag_sq();
    t_length();
    t_set_iter_pow();
}

void t_iter() {

    ejovo_seed();
    MATRIX_T *m = MATRIX_FN(rand)(5, 5);
    MATRIX_FN(print)(m);

    MATITER_T b = MATRIX_FN(row_begin)(m, 3);
    MATITER_T e = MATRIX_FN(row_end)(m, 3);

    printf("row 4: ");
    MATITER_FN(print)(b, e);

    MATITER_T b1 = MATRIX_FN(col_begin)(m, 4);
    MATITER_T e1 = MATRIX_FN(col_end)(m, 4);
    printf("col 5: ");
    MATITER_FN(print)(b1, e1);

    MATRIX_FN(free)(m);
}

// Need to assert that the products, sums, min, max are valid.
void t_diag_wide() {

    MATRIX_T *wide = get_wide();

    MATRIX_FN(print)(wide);
    MATRIX_FN(print_diag)(wide, 0);
    MATRIX_FN(print_diag)(wide, 2);
    MATRIX_FN(print_diag)(wide, -1);
    MATRIX_FN(print_diag)(wide, -2);
    MATRIX_FN(print_diag)(wide, 8);
    MATRIX_FN(print_diag)(wide, 9);

    assert(MATRIX_FN(diag_max)(wide, 0) == 7);
    assert(MATRIX_FN(diag_max)(wide, 2) == 8);
    assert(MATRIX_FN(diag_max)(wide, -1) == 9);
    assert(MATRIX_FN(diag_max)(wide, -2) == 10);
    assert(MATRIX_FN(diag_max)(wide, 8) == 9);
    assert(MATRIX_FN(diag_max)(wide, 9) == 10);

    assert(MATRIX_FN(diag_min)(wide, 0) == 0);
    assert(MATRIX_FN(diag_min)(wide, 2) == 0);
    assert(MATRIX_FN(diag_min)(wide, -1) == 3);
    assert(MATRIX_FN(diag_min)(wide, -2) == 4);
    assert(MATRIX_FN(diag_min)(wide, 8) == 5);
    assert(MATRIX_FN(diag_min)(wide, 9) == 10);

    assert(MATRIX_FN(diag_sum)(wide, 0) == 12);
    assert(MATRIX_FN(diag_sum)(wide, 2) == 24);
    assert(MATRIX_FN(diag_sum)(wide, -1) == 21);
    assert(MATRIX_FN(diag_sum)(wide, -2) == 20);
    assert(MATRIX_FN(diag_sum)(wide, 8) == 14);
    assert(MATRIX_FN(diag_sum)(wide, 9) == 10);

    assert(MATRIX_FN(diag_prod)(wide, 0) == 0);
    assert(MATRIX_FN(diag_prod)(wide, 2) == 0);
    assert(MATRIX_FN(diag_prod)(wide, -1) == 486);
    assert(MATRIX_FN(diag_prod)(wide, -2) == 240);
    assert(MATRIX_FN(diag_prod)(wide, 8) == 45);
    assert(MATRIX_FN(diag_prod)(wide, 9) == 10);

    MATRIX_FN(free)(wide);
}

void t_diag_tall() {

    MATRIX_T *tall = get_tall();

    MATRIX_FN(print)(tall);
    MATRIX_FN(print_diag)(tall, 0);
    MATRIX_FN(print_diag)(tall, 3);
    MATRIX_FN(print_diag)(tall, 2);
    MATRIX_FN(print_diag)(tall, -4);
    MATRIX_FN(print_diag)(tall, -3);
    MATRIX_FN(print_diag)(tall, -6);

    assert(MATRIX_FN(diag_max)(tall, 0) == 9);
    assert(MATRIX_FN(diag_max)(tall, 3) == 1);
    assert(MATRIX_FN(diag_max)(tall, 2) == 9);
    assert(MATRIX_FN(diag_max)(tall, -4) == 5);
    assert(MATRIX_FN(diag_max)(tall, -3) == 9);
    assert(MATRIX_FN(diag_max)(tall, -6) == 10);

    assert(MATRIX_FN(diag_min)(tall, 0) == 3);
    assert(MATRIX_FN(diag_min)(tall, 3) == 1);
    assert(MATRIX_FN(diag_min)(tall, 2) == 2);
    assert(MATRIX_FN(diag_min)(tall, -4) == 2);
    assert(MATRIX_FN(diag_min)(tall, -3) == 0);
    assert(MATRIX_FN(diag_min)(tall, -6) == 6);

    assert(MATRIX_FN(diag_sum)(tall, 0) == 23);
    assert(MATRIX_FN(diag_sum)(tall, 3) == 1);
    assert(MATRIX_FN(diag_sum)(tall, 2) == 11);
    assert(MATRIX_FN(diag_sum)(tall, -4) == 13);
    assert(MATRIX_FN(diag_sum)(tall, -3) == 25);
    assert(MATRIX_FN(diag_sum)(tall, -6) == 16);

    assert(MATRIX_FN(diag_prod)(tall, 0) == 756);
    assert(MATRIX_FN(diag_prod)(tall, 3) == 1);
    assert(MATRIX_FN(diag_prod)(tall, 2) == 18);
    assert(MATRIX_FN(diag_prod)(tall, -4) == 80);
    assert(MATRIX_FN(diag_prod)(tall, -3) == 0);
    assert(MATRIX_FN(diag_prod)(tall, -6) == 60);

    MATRIX_FN(free)(tall);
}

void t_diag_sq() {

    MATRIX_T *sq   = get_square();

    MATRIX_FN(print)(sq);
    MATRIX_FN(print_diag)(sq, 0);
    MATRIX_FN(print_diag)(sq, 3);
    MATRIX_FN(print_diag)(sq, 2);
    MATRIX_FN(print_diag)(sq, -4);
    MATRIX_FN(print_diag)(sq, -3);
    MATRIX_FN(print_diag)(sq, -5);

    assert(MATRIX_FN(diag_max)(sq, 0) == 9);
    assert(MATRIX_FN(diag_max)(sq, 3) == 7);
    assert(MATRIX_FN(diag_max)(sq, 2) == 10);
    assert(MATRIX_FN(diag_max)(sq, -4) == 9);
    assert(MATRIX_FN(diag_max)(sq, -3) == 9);
    assert(MATRIX_FN(diag_max)(sq, -5) == 8);

    assert(MATRIX_FN(diag_min)(sq, 0) == 1);
    assert(MATRIX_FN(diag_min)(sq, 3) == 3);
    assert(MATRIX_FN(diag_min)(sq, 2) == 4);
    assert(MATRIX_FN(diag_min)(sq, -4) == 0);
    assert(MATRIX_FN(diag_min)(sq, -3) == 6);
    assert(MATRIX_FN(diag_min)(sq, -5) == 2);

    assert(MATRIX_FN(diag_sum)(sq, 0) == 36);
    assert(MATRIX_FN(diag_sum)(sq, 3) == 27);
    assert(MATRIX_FN(diag_sum)(sq, 2) == 42);
    assert(MATRIX_FN(diag_sum)(sq, -4) == 21);
    assert(MATRIX_FN(diag_sum)(sq, -3) == 40);
    assert(MATRIX_FN(diag_sum)(sq, -5) == 17);

    assert(MATRIX_FN(diag_prod)(sq, 0) == 19440);
    assert(MATRIX_FN(diag_prod)(sq, 3) == 3528);
    assert(MATRIX_FN(diag_prod)(sq, 2) == 90720);
    assert(MATRIX_FN(diag_prod)(sq, -4) == 0);
    assert(MATRIX_FN(diag_prod)(sq, -3) == 31104);
    assert(MATRIX_FN(diag_prod)(sq, -5) == 112);

    MATRIX_FN(free)(sq);
}

void t_length() {

    MATRIX_T *wide = get_wide();

    MATITER_T b = MAT_FN(rowbegin)(wide, 0);
    MATITER_T e = MAT_FN(rowend)(wide, 0);

    assert(MATITER_FN(length)(b, e) == wide->ncols);

    MATRIX_FN(free)(wide);


}

void t_set_iter_pow() {

    MATRIX_T *m = VECTOR_FN(rnorm)(100, 0, 1);

    MATRIX_T *b = MATRIX_FN(rowvec)(m->data, 100);
    MATITER_FN(apply_set_iter_pow)(MATRIX_FN(begin)(b), MATRIX_FN(end)(b), MATRIX_FN(begin)(m), 2.0);

    VECTOR_FN(print_as_row)(m);
    MATRIX_FN(print)(b);




}