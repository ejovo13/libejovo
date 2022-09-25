#include "test_mat.h"


int main() {

    Matrix_d *m = Matrix_value_d(2, 2, 4);

    Matrix_print_d(m);

    printf("2-norm of first column: %lf\n", Matrix_col_norm_d(m, 0));
    // printf("3-norm of second column: %lf\n", Vector_pnorm_iter_d()

    printf("Frobenius norm: %lf\n", Matrix_frobenius_d(m));

    Vector_d*v = Vector_new_d(10);
    Vector_set_first_d(v, 50);
    Vector_set_last_d(v, 8);
    Matrix_print_d(v);
    printf("%ld\n", v->nrows);
    printf("vector size: %ld\n", Vector_size_d(v));
    printf("vector_at_last: %lf\n", Vector_at_d(v, Vector_size_d(v) - 1));

    Matrix_print_d(Vector_linspace_d(0, 1, 2));

    Matrix_print_iter_d(Matrix_anon_d(Vector_linspace_d(0.0, 2.0, 15)));


    Matrix_anon_free_d();
    Matrix_free_d(v);
    Matrix_free_d(m);

    return 0;
}