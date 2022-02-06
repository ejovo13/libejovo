#include "test_mat.h"
#include <stdint.h>
#include "ejovo_bin.h"

void t_unif();
void t_norm();

int main() {

    ejovo_seed();

    t_unif();
    t_norm();

    return 0;
}

void t_unif() {

    Vector *v = Vector_runif(1000000, 0, 10);

    printf("========== Uniform [0, 10] ==========\n");
    printf("Mean(v): %lf\n", Vector_iter_mean(v));
    printf("std(v): %lf\n", Vector_iter_std(v));
    printf("var(v): %lf\n", Vector_iter_var(v));

    Matrix_free(v);

}

void t_norm() {

    Vector *v = Vector_rnorm(1000000, 0, 1);

    printf("========== Norm [0, 1] ==========\n");
    printf("Mean(v): %lf\n", Vector_iter_mean(v));
    printf("std(v): %lf\n", Vector_iter_std(v));
    printf("var(v): %lf\n", Vector_iter_var(v));

    Matrix_free(v);
}