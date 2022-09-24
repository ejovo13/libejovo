#include "ejovo_matrix_generic.h"

bool outside_std (double x) {
    return x < -1 || x > 1;
}

int main() {

    ejovo_seed();

    Vector *v = TYPED_FN(asrow)(linspace_d(-2, 5, 15));
    Vector *v_exp = map_d(v, exp);

    MATRIX_FN(print)(v);
    MATRIX_FN(print)(v_exp);

    MATRIX_FN(reset)(&v);

    v = VECTOR_FN(rnorm)(15, 0, 1);

    MATRIX_FN(print)(v);

    Vector *outliers = TYPED_FN(filter)(v, outside_std);
    Vector *values = TYPED_FN(filter_if_not)(v, outside_std);

    MATRIX_FN(print)(outliers);
    MATRIX_FN(print)(values);

    return 0;

}