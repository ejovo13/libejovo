#include "ejovo_matrix_generic.h"

bool outside_std (double x) {
    return x < -1 || x > 1;
}

int main() {

    ejovo_seed();

    Vector_d*v = asrow_d(linspace_d(-2, 5, 15));
    Vector_d*v_exp = map_d(v, exp);

    Matrix_print_d(v);
    Matrix_print_d(v_exp);

    Matrix_reset_d(&v);

    v = Vector_rnorm_d(15, 0, 1);

    Matrix_print_d(v);

    Vector_d*outliers = filter_d(v, outside_std);
    Vector_d*values = filter_if_not_d(v, outside_std);

    Matrix_print_d(outliers);
    Matrix_print_d(values);

    return 0;

}