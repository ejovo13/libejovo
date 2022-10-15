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

    Vector_d*v = Vector_rnorm_d(100, 0, 1);

    v->ncols = 10;
    v->nrows = 10;

    Matrix_print_d(v);

    Vector_d*neg = filter_d(v, is_neg);
    Vector_d*pos = filter_if_not_d(v, is_neg);

    Matrix_print_d(neg);
    Matrix_print_d(pos);

    Vector_d*r = range_d(1, 10, 2);
    Matrix_print_d(r);

    // Get the first 10 elements of a vector;

    Vector_d *v_take = take_d(v, 10);
    Matrix_print_d(v_take);



}