#include "ejovo_matrix_generic.h"
#include <assert.h>
#include <stdbool.h>

// Try to define two types of matrices

int main() {

    ejovo_seed();

    // Matrix_d *md = Matrix_rand_d(10, 2);
    // Matrix_i *mi = Matrix_random_i(10, 2, 0, 100);
    // Matrix_f *mf = Matrix_new_f(10, 2);

    Matrix_c *mc = Matrix_runif_c(5, 2, __builtin_complex(1., 0.), __builtin_complex(0., 10.));
    Matrix_c *mc1 = Matrix_value_c(5, 2, 2);

    Matrix_print_c(mc);
    Matrix_print_c(mc1);

    Matrix_print_c(Matrix_add_c(mc, mc1));
    Matrix_print_c(Matrix_hadamard_c(mc, mc1));

    // Let me see how some random numbers behave

    Matrix_i *indices = runif_i(10000000, 0, 100);
    printf("mean: %lf", sum_i(indices) / (double) Matrix_size_i(indices));

    printf("max_i: %d\n", max_i(indices));

    // Matrix_print_i(indices);

    Matrix_i *vec = Matrix_new_i(4, 3);

    for (int i = 0; i < 12; i++) {
        vec->data[i] = i;
    }

    Matrix_print_i(vec);


    return 0;
}