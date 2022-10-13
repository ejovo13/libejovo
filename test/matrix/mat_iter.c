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
    Matrix_d *m = Matrix_rand_d(5, 5);
    Matrix_print_d(m);

    MatIter_d b = Matrix_row_begin_d(m, 3);
    MatIter_d e = Matrix_row_end_d(m, 3);

    printf("row 4: ");
    MatIter_print_d(b, e);

    MatIter_d b1 = Matrix_col_begin_d(m, 4);
    MatIter_d e1 = Matrix_col_end_d(m, 4);
    printf("col 5: ");
    MatIter_print_d(b1, e1);

    Matrix_free_d(m);
}

// Need to assert that the products, sums, min, max are valid.
void t_diag_wide() {

    Matrix_d *wide = get_wide();

    Matrix_print_d(wide);
    Matrix_print_diag_d(wide, 0);
    Matrix_print_diag_d(wide, 2);
    Matrix_print_diag_d(wide, -1);
    Matrix_print_diag_d(wide, -2);
    Matrix_print_diag_d(wide, 8);
    Matrix_print_diag_d(wide, 9);

    assert(Matrix_diag_max_d(wide, 0) == 7);
    assert(Matrix_diag_max_d(wide, 2) == 8);
    assert(Matrix_diag_max_d(wide, -1) == 9);
    assert(Matrix_diag_max_d(wide, -2) == 10);
    assert(Matrix_diag_max_d(wide, 8) == 9);
    assert(Matrix_diag_max_d(wide, 9) == 10);

    assert(Matrix_diag_min_d(wide, 0) == 0);
    assert(Matrix_diag_min_d(wide, 2) == 0);
    assert(Matrix_diag_min_d(wide, -1) == 3);
    assert(Matrix_diag_min_d(wide, -2) == 4);
    assert(Matrix_diag_min_d(wide, 8) == 5);
    assert(Matrix_diag_min_d(wide, 9) == 10);

    assert(Matrix_diag_sum_d(wide, 0) == 12);
    assert(Matrix_diag_sum_d(wide, 2) == 24);
    assert(Matrix_diag_sum_d(wide, -1) == 21);
    assert(Matrix_diag_sum_d(wide, -2) == 20);
    assert(Matrix_diag_sum_d(wide, 8) == 14);
    assert(Matrix_diag_sum_d(wide, 9) == 10);

    assert(Matrix_diag_prod_d(wide, 0) == 0);
    assert(Matrix_diag_prod_d(wide, 2) == 0);
    assert(Matrix_diag_prod_d(wide, -1) == 486);
    assert(Matrix_diag_prod_d(wide, -2) == 240);
    assert(Matrix_diag_prod_d(wide, 8) == 45);
    assert(Matrix_diag_prod_d(wide, 9) == 10);

    Matrix_free_d(wide);
}

void t_diag_tall() {

    Matrix_d *tall = get_tall();

    Matrix_print_d(tall);
    Matrix_print_diag_d(tall, 0);
    Matrix_print_diag_d(tall, 3);
    Matrix_print_diag_d(tall, 2);
    Matrix_print_diag_d(tall, -4);
    Matrix_print_diag_d(tall, -3);
    Matrix_print_diag_d(tall, -6);

    assert(Matrix_diag_max_d(tall, 0) == 9);
    assert(Matrix_diag_max_d(tall, 3) == 1);
    assert(Matrix_diag_max_d(tall, 2) == 9);
    assert(Matrix_diag_max_d(tall, -4) == 5);
    assert(Matrix_diag_max_d(tall, -3) == 9);
    assert(Matrix_diag_max_d(tall, -6) == 10);

    assert(Matrix_diag_min_d(tall, 0) == 3);
    assert(Matrix_diag_min_d(tall, 3) == 1);
    assert(Matrix_diag_min_d(tall, 2) == 2);
    assert(Matrix_diag_min_d(tall, -4) == 2);
    assert(Matrix_diag_min_d(tall, -3) == 0);
    assert(Matrix_diag_min_d(tall, -6) == 6);

    assert(Matrix_diag_sum_d(tall, 0) == 23);
    assert(Matrix_diag_sum_d(tall, 3) == 1);
    assert(Matrix_diag_sum_d(tall, 2) == 11);
    assert(Matrix_diag_sum_d(tall, -4) == 13);
    assert(Matrix_diag_sum_d(tall, -3) == 25);
    assert(Matrix_diag_sum_d(tall, -6) == 16);

    assert(Matrix_diag_prod_d(tall, 0) == 756);
    assert(Matrix_diag_prod_d(tall, 3) == 1);
    assert(Matrix_diag_prod_d(tall, 2) == 18);
    assert(Matrix_diag_prod_d(tall, -4) == 80);
    assert(Matrix_diag_prod_d(tall, -3) == 0);
    assert(Matrix_diag_prod_d(tall, -6) == 60);

    Matrix_free_d(tall);
}

void t_diag_sq() {

    Matrix_d *sq   = get_square();

    Matrix_print_d(sq);
    Matrix_print_diag_d(sq, 0);
    Matrix_print_diag_d(sq, 3);
    Matrix_print_diag_d(sq, 2);
    Matrix_print_diag_d(sq, -4);
    Matrix_print_diag_d(sq, -3);
    Matrix_print_diag_d(sq, -5);

    assert(Matrix_diag_max_d(sq, 0) == 9);
    assert(Matrix_diag_max_d(sq, 3) == 7);
    assert(Matrix_diag_max_d(sq, 2) == 10);
    assert(Matrix_diag_max_d(sq, -4) == 9);
    assert(Matrix_diag_max_d(sq, -3) == 9);
    assert(Matrix_diag_max_d(sq, -5) == 8);

    assert(Matrix_diag_min_d(sq, 0) == 1);
    assert(Matrix_diag_min_d(sq, 3) == 3);
    assert(Matrix_diag_min_d(sq, 2) == 4);
    assert(Matrix_diag_min_d(sq, -4) == 0);
    assert(Matrix_diag_min_d(sq, -3) == 6);
    assert(Matrix_diag_min_d(sq, -5) == 2);

    assert(Matrix_diag_sum_d(sq, 0) == 36);
    assert(Matrix_diag_sum_d(sq, 3) == 27);
    assert(Matrix_diag_sum_d(sq, 2) == 42);
    assert(Matrix_diag_sum_d(sq, -4) == 21);
    assert(Matrix_diag_sum_d(sq, -3) == 40);
    assert(Matrix_diag_sum_d(sq, -5) == 17);

    assert(Matrix_diag_prod_d(sq, 0) == 19440);
    assert(Matrix_diag_prod_d(sq, 3) == 3528);
    assert(Matrix_diag_prod_d(sq, 2) == 90720);
    assert(Matrix_diag_prod_d(sq, -4) == 0);
    assert(Matrix_diag_prod_d(sq, -3) == 31104);
    assert(Matrix_diag_prod_d(sq, -5) == 112);

    Matrix_free_d(sq);
}

void t_length() {

    Matrix_d *wide = get_wide();

    MatIter_d b = matrowbegin_d(wide, 0);
    MatIter_d e = matrowend_d(wide, 0);

    rassert(MatIter_length_d(b, e) == wide->ncols);

    Matrix_free_d(wide);


}

void t_set_iter_pow() {

    Matrix_d *m = Vector_rnorm_d(100, 0, 1);

    Matrix_d *b = Matrix_rowvec_d(m->data, 100);
    MatIter_apply_set_iter_pow_d(Matrix_begin_d(b), Matrix_end_d(b), Matrix_begin_d(m), 2.0);

    Vector_print_as_row_d(m);
    Matrix_print_d(b);




}