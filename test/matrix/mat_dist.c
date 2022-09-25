#include "test_mat.h"

void t_unif();
void t_norm();
void t_exp();

int main() {

    ejovo_seed();

    t_unif();
    t_norm();
    t_exp();

    return 0;
}

void t_unif() {

    Vector_d*v = Vector_runif_d(100000, 0, 10);

    printf("========== Uniform [0, 10] ==========\n");
    printf("Mean(v): %lf\n", Vector_iter_mean_d(v));
    printf("std_d(v): %lf\n", Vector_iter_std_d(v));
    printf("var_d(v): %lf\n", Vector_iter_var_d(v));

    Matrix_free_d(v);

}

void t_norm() {

    Vector_d*v = Vector_rnorm_d(100000, 0, 1);

    printf("========== Norm [0, 1] ==========\n");
    printf("Mean(v): %lf\n", Vector_iter_mean_d(v));
    printf("std_d(v): %lf\n", Vector_iter_std_d(v));
    printf("var_d(v): %lf\n", Vector_iter_var_d(v));

    Matrix_free_d(v);
}

void t_exp() {

    Vector_d*v = Vector_rexp_d(100000, 5);

    printf("========== Exp [5] ==========\n");
    printf("Mean(v): %lf\n", Vector_iter_mean_d(v));
    printf("std_d(v): %lf\n", Vector_iter_std_d(v));
    printf("var(v): %lf\n", Vector_iter_var_d(v));

    Matrix_free_d(v);

}