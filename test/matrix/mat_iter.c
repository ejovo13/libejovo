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
    Matrix *m = Matrix_rand(5, 5);
    Matrix_print(m);

    MatIter b = Matrix_row_begin(m, 3);
    MatIter e = Matrix_row_end(m, 3);

    printf("row 4: ");
    MatIter_print(b, e);

    MatIter b1 = Matrix_col_begin(m, 4);
    MatIter e1 = Matrix_col_end(m, 4);
    printf("col 5: ");
    MatIter_print(b1, e1);

    Matrix_free(m);
}

// Need to assert that the products, sums, min, max are valid.
void t_diag_wide() {

    Matrix *wide = get_wide();

    Matrix_print(wide);
    Matrix_print_diag(wide, 0);
    Matrix_print_diag(wide, 2);
    Matrix_print_diag(wide, -1);
    Matrix_print_diag(wide, -2);
    Matrix_print_diag(wide, 8);
    Matrix_print_diag(wide, 9);

    assert(Matrix_diag_max(wide, 0) == 7);
    assert(Matrix_diag_max(wide, 2) == 8);
    assert(Matrix_diag_max(wide, -1) == 9);
    assert(Matrix_diag_max(wide, -2) == 10);
    assert(Matrix_diag_max(wide, 8) == 9);
    assert(Matrix_diag_max(wide, 9) == 10);

    assert(Matrix_diag_min(wide, 0) == 0);
    assert(Matrix_diag_min(wide, 2) == 0);
    assert(Matrix_diag_min(wide, -1) == 3);
    assert(Matrix_diag_min(wide, -2) == 4);
    assert(Matrix_diag_min(wide, 8) == 5);
    assert(Matrix_diag_min(wide, 9) == 10);

    assert(Matrix_diag_sum(wide, 0) == 12);
    assert(Matrix_diag_sum(wide, 2) == 24);
    assert(Matrix_diag_sum(wide, -1) == 21);
    assert(Matrix_diag_sum(wide, -2) == 20);
    assert(Matrix_diag_sum(wide, 8) == 14);
    assert(Matrix_diag_sum(wide, 9) == 10);

    assert(Matrix_diag_prod(wide, 0) == 0);
    assert(Matrix_diag_prod(wide, 2) == 0);
    assert(Matrix_diag_prod(wide, -1) == 486);
    assert(Matrix_diag_prod(wide, -2) == 240);
    assert(Matrix_diag_prod(wide, 8) == 45);
    assert(Matrix_diag_prod(wide, 9) == 10);

    Matrix_free(wide);
}

void t_diag_tall() {

    Matrix *tall = get_tall();

    Matrix_print(tall);
    Matrix_print_diag(tall, 0);
    Matrix_print_diag(tall, 3);
    Matrix_print_diag(tall, 2);
    Matrix_print_diag(tall, -4);
    Matrix_print_diag(tall, -3);
    Matrix_print_diag(tall, -6);

    assert(Matrix_diag_max(tall, 0) == 9);
    assert(Matrix_diag_max(tall, 3) == 1);
    assert(Matrix_diag_max(tall, 2) == 9);
    assert(Matrix_diag_max(tall, -4) == 5);
    assert(Matrix_diag_max(tall, -3) == 9);
    assert(Matrix_diag_max(tall, -6) == 10);

    assert(Matrix_diag_min(tall, 0) == 3);
    assert(Matrix_diag_min(tall, 3) == 1);
    assert(Matrix_diag_min(tall, 2) == 2);
    assert(Matrix_diag_min(tall, -4) == 2);
    assert(Matrix_diag_min(tall, -3) == 0);
    assert(Matrix_diag_min(tall, -6) == 6);

    assert(Matrix_diag_sum(tall, 0) == 23);
    assert(Matrix_diag_sum(tall, 3) == 1);
    assert(Matrix_diag_sum(tall, 2) == 11);
    assert(Matrix_diag_sum(tall, -4) == 13);
    assert(Matrix_diag_sum(tall, -3) == 25);
    assert(Matrix_diag_sum(tall, -6) == 16);

    assert(Matrix_diag_prod(tall, 0) == 756);
    assert(Matrix_diag_prod(tall, 3) == 1);
    assert(Matrix_diag_prod(tall, 2) == 18);
    assert(Matrix_diag_prod(tall, -4) == 80);
    assert(Matrix_diag_prod(tall, -3) == 0);
    assert(Matrix_diag_prod(tall, -6) == 60);

    Matrix_free(tall);
}

void t_diag_sq() {

    Matrix *sq   = get_square();

    Matrix_print(sq);
    Matrix_print_diag(sq, 0);
    Matrix_print_diag(sq, 3);
    Matrix_print_diag(sq, 2);
    Matrix_print_diag(sq, -4);
    Matrix_print_diag(sq, -3);
    Matrix_print_diag(sq, -5);

    assert(Matrix_diag_max(sq, 0) == 9);
    assert(Matrix_diag_max(sq, 3) == 7);
    assert(Matrix_diag_max(sq, 2) == 10);
    assert(Matrix_diag_max(sq, -4) == 9);
    assert(Matrix_diag_max(sq, -3) == 9);
    assert(Matrix_diag_max(sq, -5) == 8);

    assert(Matrix_diag_min(sq, 0) == 1);
    assert(Matrix_diag_min(sq, 3) == 3);
    assert(Matrix_diag_min(sq, 2) == 4);
    assert(Matrix_diag_min(sq, -4) == 0);
    assert(Matrix_diag_min(sq, -3) == 6);
    assert(Matrix_diag_min(sq, -5) == 2);

    assert(Matrix_diag_sum(sq, 0) == 36);
    assert(Matrix_diag_sum(sq, 3) == 27);
    assert(Matrix_diag_sum(sq, 2) == 42);
    assert(Matrix_diag_sum(sq, -4) == 21);
    assert(Matrix_diag_sum(sq, -3) == 40);
    assert(Matrix_diag_sum(sq, -5) == 17);

    assert(Matrix_diag_prod(sq, 0) == 19440);
    assert(Matrix_diag_prod(sq, 3) == 3528);
    assert(Matrix_diag_prod(sq, 2) == 90720);
    assert(Matrix_diag_prod(sq, -4) == 0);
    assert(Matrix_diag_prod(sq, -3) == 31104);
    assert(Matrix_diag_prod(sq, -5) == 112);

    Matrix_free(sq);
}

void t_length() {

    Matrix *wide = get_wide();

    MatIter b = matrowbegin(wide, 0);
    MatIter e = matrowend(wide, 0);

    assert(MatIter_length(b, e) == wide->ncols);

    Matrix_free(wide);


}

void t_set_iter_pow() {

    Matrix *m = Vector_rnorm(100, 0, 1);

    Matrix *b = Matrix_rowvec(m->data, 100);
    MatIter_apply_set_iter_pow(Matrix_begin(b), Matrix_end(b), Matrix_begin(m), 2.0);

    Vector_print_as_row(m);
    Matrix_print(b);




}