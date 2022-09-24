#include "test_mat.h"

void t_func();

int main() {

    ejovo_seed();

    t_func();

    return 0;
}


bool eq10(double x) {
    return x == 10;
}

static bool is_neg(double x) {
    return x < 0;
}

void t_func() {

    // let's test the functional patterns

    // let's start by generating a new matrix

    Vector *v = VECTOR_FN(rnorm)(100, 0, 1);

    v->ncols = 10;
    v->nrows = 10;

    MATRIX_FN(print)(v);

    Vector *neg = TYPED_FN(filter)(v, is_neg);
    Vector *pos = TYPED_FN(filter_if_not)(v, is_neg);

    MATRIX_FN(print)(neg);
    MATRIX_FN(print)(pos);

    Vector *r = range_d(1, 10, 2);
    MATRIX_FN(print)(r);




}