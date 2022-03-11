#include "ejovo_matrix.h"

bool outside_std(double x) {
    return x < -1 || x > 1;
}

int main() {

    ejovo_seed();

    Vector *v = asrow(linspace(-2, 5, 15));
    Vector *v_exp = map(v, exp);

    Matrix_print(v);
    Matrix_print(v_exp);

    Matrix_reset(&v);

    v = Vector_rnorm(15, 0, 1);

    Matrix_print(v);

    Vector *outliers = filter(v, outside_std);
    Vector *values = filter_if_not(v, outside_std);

    Matrix_print(outliers);
    Matrix_print(values);

    return 0;

}