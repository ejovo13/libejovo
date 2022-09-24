#include "ejovo_matrix_generic.h"

int main() {

    ejovo_seed();

    // MATRIX_T *stoch = MATRIX_FN(as_stochastic)(MATRIX_FN(runif)(10, 10, 0, 5));
    // MATRIX_T *stoch = MATRIX_FN(as_stochastic)(MATRIX_FN(runif)(2, 2, 0, 5));

    // MATRIX_T *stoch = TYPED_FN(Stochastic_rexp)(5, 3);
    MATRIX_T *stoch_norm = TYPED_FN(Stochastic_rnorm)(5, 0, 1);
    MATRIX_T *stoch_exp = TYPED_FN(Stochastic_rexp)(5, 3);
    MATRIX_T *stoch_unif = TYPED_FN(Stochastic_runif)(5, 0, 10);

    // MATRIX_FN(print)(stoch);

    printf("P_ij ~ N(0, 1)\n");

    // MATRIX_FN(print)(stoch_norm);
    // printf("P_ij ~ U(0, 10)\n");
    MATRIX_FN(print)(stoch_unif);
    // printf("P_ij ~ exp(rate = 3)\n");
    // MATRIX_FN(print)(stoch_exp);

    Vector *dist = TYPED_FN(asrow)(VECTOR_FN(prob_unif)(4));

    MATRIX_FN(print)(dist);

    // Let's print our matrices raised to a stupid high power????

    for (int i = 0; i < 11; i++) {

        printf("============= n : %d ==============\n", i);
        MATRIX_FN(print)(MATRIX_FN(pow)(stoch_unif, i));
    }

    MATRIX_T *mat_conv = MATRIX_FN(pow)(stoch_unif, 50);

    Vector *vec_stationary = MATRIX_FN(get_row)(mat_conv, 0);

    // MATRIX_FN(print)(vec_stationary);

    // printf("MATRIX_T multiplication::\n");

    printf("First row of A^50\n");

    VECTOR_FN(print_as_row)(vec_stationary);

    printf("\n");

    MATRIX_T *transition_applied = MATRIX_FN(multiply)(vec_stationary, stoch_unif);

    Vector *error = MATRIX_FN(subtract)(transition_applied, vec_stationary);

    printf("||error||_2 : %lf\n", VECTOR_FN(distance)(transition_applied, vec_stationary));


    MATRIX_T *p = MATRIX_FN(from)((double []) {1, 0, 0, 0, 0, .5, 0, .5, 0, 0, 0, .5, 0, .5, 0, 0, 0, .5, 0, .5, 0, 0, 0, 0, 1}, 5, 5);

    printf("Joueur ruine: \n");
    MATRIX_FN(print)(p);

    Vector *v = MATRIX_FN(from)((double []) {.2, .2, .2, .2, .2}, 1, 5);

    printf("Convergence de matrice de transition:\n");
    MATRIX_FN(print)(MATRIX_FN(pow)(p, 50));
    // MATRIX_FN(print)(MATRIX_FN(pow)(p, 2));

    // MATRIX_FN(print)(MATRIX_FN(multiply)(v, MATRIX_FN(pow)(p, 2)));

    MATRIX_T *m = MATRIX_FN(runif)(10, 10, 0, 5);

    MATRIX_FN(print)(m);

    // MATRIX_FN(print)(MATRIX_FN(anon)(TYPED_FN(as_stochastic)(MATRIX_FN(clone)(m))));

    printf("------- Double Stochastic Tests ---------\n");

    MATRIX_FN(print)(m);

    MATRIX_T *m_pos = TYPED_FN(map)(m, fabs);

    MATRIX_FN(print)(TYPED_FN(as_doubly_stochastic)(m_pos));
    // v = MATRIX_FN(value)(3, 1, 1.0);
    // Vector *u = MATRIX_FN(value)(3, 1, 1.0);


    // Let's check out the new distance functions.
    // Vector *diff = VECTOR_FN(difference)(v, u);

    // MATRIX_FN(print)(diff);

    // printf("Distance between u and v: %lf\n", VECTOR_FN(distance)(u, v));

    MATRIX_FN(print)(MATRIX_FN(pow)(m_pos, 10));


    // Markov chain "something de Ehrenfast" idfk...
    MATRIX_T *ehren = MATRIX_FN(from)((double []) {0, 1, 0, 0, .5, 0, .5, 0, 0, .5, 0, .5, 0, 0, 1, 0}, 4, 4);

    MATRIX_FN(print)(ehren);

    MATRIX_T *ehren_stable = MATRIX_FN(pow)(ehren, 20);

    MATRIX_FN(print)(ehren_stable);

    MATRIX_FN(print)(TYPED_FN(gausselim)(ehren_stable, NULL));

    MATRIX_T *rainy = MATRIX_FN(from)((double []) {0.6, .4, .2, .8}, 2, 2);
    MATRIX_FN(print)(MATRIX_FN(pow)(rainy, 20));


    return 0;
}