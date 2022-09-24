#include "ejovo_matrix.h"

bool outside_std(double x) {
    return x < -1 || x > 1;
}

int main() {

    ejovo_seed();

    Vector *v = asrow(linspace(-2, 5, 15));
    Vector *v_exp = map(v, exp);

    MATRIX_FN(print)(v);
    MATRIX_FN(print)(v_exp);

    MATRIX_FN(reset)(&v);

    v = VECTOR_FN(rnorm)(15, 0, 1);

    MATRIX_FN(print)(v);

    Vector *outliers = filter(v, outside_std);
    Vector *values = filter_if_not(v, outside_std);

    MATRIX_FN(print)(outliers);
    MATRIX_FN(print)(values);

    return 0;

}