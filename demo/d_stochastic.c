#include "ejovo_matrix_generic.h"

int main() {

    ejovo_seed();

    // Matrix_d *stoch = Matrix_as_stochastic_d(Matrix_runif_d(10, 10, 0, 5));
    // Matrix_d *stoch = Matrix_as_stochastic_d(Matrix_runif_d(2, 2, 0, 5));

    // Matrix_d *stoch = Stochastic_rexp_d(5, 3);
    Matrix_d *stoch_norm = Stochastic_rnorm_d(5, 0, 1);
    Matrix_d *stoch_exp = Stochastic_rexp_d(5, 3);
    Matrix_d *stoch_unif = Stochastic_runif_d(5, 0, 10);

    // Matrix_print_d(stoch);

    printf("P_ij ~ N(0, 1)\n");

    // Matrix_print_d(stoch_norm);
    // printf("P_ij ~ U(0, 10)\n");
    Matrix_print_d(stoch_unif);
    // printf("P_ij ~ exp(rate = 3)\n");
    // Matrix_print_d(stoch_exp);

    Vector_d*dist = asrow_d(Vector_prob_unif_d(4));

    Matrix_print_d(dist);

    // Let's print our matrices raised to a stupid high power????

    for (int i = 0; i < 11; i++) {

        printf("============= n : %d ==============\n", i);
        Matrix_print_d(Matrix_pow_d(stoch_unif, i));
    }

    Matrix_d *mat_conv = Matrix_pow_d(stoch_unif, 50);

    Vector_d*vec_stationary = Matrix_get_row_d(mat_conv, 0);

    // Matrix_print_d(vec_stationary);

    // printf("Matrix_d multiplication::\n");

    printf("First row of A^50\n");

    Vector_print_as_row_d(vec_stationary);

    printf("\n");

    Matrix_d *transition_applied = Matrix_multiply_d(vec_stationary, stoch_unif);

    Vector_d*error = Matrix_subtract_d(transition_applied, vec_stationary);

    printf("||error||_2 : %lf\n", Vector_distance_d(transition_applied, vec_stationary));


    Matrix_d *p = Matrix_from_d((double []) {1, 0, 0, 0, 0, .5, 0, .5, 0, 0, 0, .5, 0, .5, 0, 0, 0, .5, 0, .5, 0, 0, 0, 0, 1}, 5, 5);

    printf("Joueur ruine: \n");
    Matrix_print_d(p);

    Vector_d*v = Matrix_from_d((double []) {.2, .2, .2, .2, .2}, 1, 5);

    printf("Convergence de matrice de transition:\n");
    Matrix_print_d(Matrix_pow_d(p, 50));
    // Matrix_print_d(Matrix_pow_d(p, 2));

    // Matrix_print_d(Matrix_multiply_d(v, Matrix_pow_d(p, 2)));

    Matrix_d *m = Matrix_runif_d(10, 10, 0, 5);

    Matrix_print_d(m);

    // Matrix_print_d(Matrix_anon_d(as_stochastic_d(Matrix_clone_d(m))));

    printf("------- Double Stochastic Tests ---------\n");

    Matrix_print_d(m);

    Matrix_d *m_pos = map_d(m, fabs);

    Matrix_print_d(as_doubly_stochastic_d(m_pos));
    // v = Matrix_value_d(3, 1, 1.0);
    // Vector_d*u = Matrix_value_d(3, 1, 1.0);


    // Let's check out the new distance functions.
    // Vector_d*diff = Vector_difference_d(v, u);

    // Matrix_print_d(diff);

    // printf("Distance between u and v: %lf\n", Vector_distance_d(u, v));

    Matrix_print_d(Matrix_pow_d(m_pos, 10));


    // Markov chain "something de Ehrenfast" idfk...
    Matrix_d *ehren = Matrix_from_d((double []) {0, 1, 0, 0, .5, 0, .5, 0, 0, .5, 0, .5, 0, 0, 1, 0}, 4, 4);

    Matrix_print_d(ehren);

    Matrix_d *ehren_stable = Matrix_pow_d(ehren, 20);

    Matrix_print_d(ehren_stable);

    Matrix_print_d(gausselim_d(ehren_stable, NULL));

    Matrix_d *rainy = Matrix_from_d((double []) {0.6, .4, .2, .8}, 2, 2);
    Matrix_print_d(Matrix_pow_d(rainy, 20));

    Matrix_free_d(v);
    Matrix_free_d(error);
    Matrix_free_d(stoch_exp);
    Matrix_free_d(stoch_norm);

    return 0;
}