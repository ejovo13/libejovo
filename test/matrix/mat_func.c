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

    Vector *v = Vector_rnorm(100, 0, 1);

    v->ncols = 10;
    v->nrows = 10;

    Matrix_print(v);

    Vector *neg = filter(v, is_neg);
    Vector *pos = filter_if_not(v, is_neg);

    Matrix_print(neg);
    Matrix_print(pos);

    Vector *r = range(1, 10, 2);
    Matrix_print(r);




}