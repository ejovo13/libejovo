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

    Vector *v = Vector_runif(100000, 0, 10);

    printf("========== Uniform [0, 10] ==========\n");
    printf("Mean(v): %lf\n", Vector_iter_mean(v));
    printf("std(v): %lf\n", Vector_iter_std(v));
    printf("var(v): %lf\n", Vector_iter_var(v));

    Matrix_free(v);

}

void t_norm() {

    Vector *v = Vector_rnorm(100000, 0, 1);

    printf("========== Norm [0, 1] ==========\n");
    printf("Mean(v): %lf\n", Vector_iter_mean(v));
    printf("std(v): %lf\n", Vector_iter_std(v));
    printf("var(v): %lf\n", Vector_iter_var(v));

    Matrix_free(v);
}

void t_exp() {

    Vector *v = Vector_rexp(100000, 5);

    printf("========== Exp [5] ==========\n");
    printf("Mean(v): %lf\n", Vector_iter_mean(v));
    printf("std(v): %lf\n", Vector_iter_std(v));
    printf("var(v): %lf\n", Vector_iter_var(v));

    Matrix_free(v);

}