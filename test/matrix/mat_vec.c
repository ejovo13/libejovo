#include "test_mat.h"


int main() {

    MATRIX_T *m = MATRIX_FN(value)(2, 2, 4);

    MATRIX_FN(print)(m);

    printf("2-norm of first column: %lf\n", MATRIX_FN(col_norm)(m, 0));
    // printf("3-norm of second column: %lf\n", VECTOR_FN(pnorm_iter)()

    printf("Frobenius norm: %lf\n", MATRIX_FN(frobenius)(m));

    Vector *v = VECTOR_FN(new)(10);
    VECTOR_FN(set_first)(v, 50);
    VECTOR_FN(set_last)(v, 8);
    MATRIX_FN(print)(v);
    printf("%ld\n", v->nrows);
    printf("vector size: %ld\n", VECTOR_FN(size)(v));
    printf("vector_at_last: %lf\n", VECTOR_FN(at)(v, VECTOR_FN(size)(v) - 1));

    MATRIX_FN(print)(VECTOR_FN(linspace)(0, 1, 2));

    MATRIX_FN(print_iter)(MATRIX_FN(anon)(VECTOR_FN(linspace)(0.0, 2.0, 15)));


    MATRIX_FN(anon_free)();
    MATRIX_FN(free)(v);
    MATRIX_FN(free)(m);

    return 0;
}