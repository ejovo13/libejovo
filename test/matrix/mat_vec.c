#include "test_mat.h"


int main() {

    Matrix *m = Matrix_value(2, 2, 4);

    Matrix_print(m);

    printf("2-norm of first column: %lf\n", Matrix_col_norm(m, 0));
    // printf("3-norm of second column: %lf\n", Vector_pnorm_iter()

    printf("Frobenius norm: %lf\n", Matrix_frobenius(m));

    Vector *v = Vector_new(10);
    Vector_set_first(v, 50);
    Vector_set_last(v, 8);
    Matrix_print(v);
    printf("%ld\n", v->nrows);
    printf("vector size: %ld\n", Vector_size(v));
    printf("vector_at_last: %lf\n", Vector_at(v, Vector_size(v) - 1));

    Matrix_print_iter(Matrix_anon(Vector_linspace(0.0, 2.0, 15)));


    Matrix_anon_free();
    Matrix_free(v);
    Matrix_free(m);

    return 0;
}