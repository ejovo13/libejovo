#include "ejovo_matrix.h"

int main() {

    ejovo_seed();

    // Matrix *stoch = Matrix_as_stochastic(Matrix_runif(10, 10, 0, 5));
    // Matrix *stoch = Matrix_as_stochastic(Matrix_runif(2, 2, 0, 5));

    // Matrix *stoch = Stochastic_rexp(5, 3);
    Matrix *stoch_norm = Stochastic_rnorm(5, 0, 1);
    Matrix *stoch_exp = Stochastic_rexp(5, 3);
    Matrix *stoch_unif = Stochastic_runif(10, 0, 10);

    // Matrix_print(stoch);

    printf("P_ij ~ N(0, 1)\n");

    // Matrix_print(stoch_norm);
    // printf("P_ij ~ U(0, 10)\n");
    Matrix_print(stoch_unif);
    // printf("P_ij ~ exp(rate = 3)\n");
    // Matrix_print(stoch_exp);

    Vector *dist = asrow(Vector_prob_unif(4));

    Matrix_print(dist);

    // Let's print our matrices raised to a stupid high power????

    for (int i = 0; i < 10; i++) {

        printf("============= n : %d ==============\n", i);
        Matrix_print(Matrix_pow(stoch_unif, i));
    }

    Matrix *mat_conv = Matrix_pow(stoch_unif, 50);

    Vector *vec_stationary = Matrix_get_row(mat_conv, 0);

    // Matrix_print(vec_stationary);

    // printf("Matrix multiplication::\n");

    printf("First row of A^50\n");

    Vector_print_as_row(vec_stationary);

    printf("\n");

    Matrix *transition_applied = Matrix_multiply(vec_stationary, stoch_unif);

    Vector *error = Matrix_subtract(transition_applied, vec_stationary);

    printf("||error||_2 : %lf\n", Vector_norm(error));


    Matrix *p = Matrix_from((double []) {1, 0, 0, 0, 0, .5, 0, .5, 0, 0, 0, .5, 0, .5, 0, 0, 0, .5, 0, .5, 0, 0, 0, 0, 1}, 5, 5);

    printf("Joueur ruine: \n");
    Matrix_print(p);

    Vector *v = Matrix_from((double []) {.2, .2, .2, .2, .2}, 1, 5);

    printf("Convergence de matrice de transition:\n");
    Matrix_print(Matrix_pow(p, 50));
    // Matrix_print(Matrix_pow(p, 2));

    // Matrix_print(Matrix_multiply(v, Matrix_pow(p, 2)));

    Matrix *m = Matrix_runif(10, 10, 0, 5);

    Matrix_print(m);

    // Matrix_print(Matrix_anon(as_stochastic(Matrix_clone(m))));

    printf("------- Double Stochastic Tests ---------\n");

    Matrix_print(m);

    Matrix *m_pos = map(m, fabs);

    Matrix_print(as_doubly_stochastic(m_pos));
    // v = Matrix_value(3, 1, 1.0);
    // Vector *u = Matrix_value(3, 1, 1.0);


    // Let's check out the new distance functions.
    // Vector *diff = Vector_difference(v, u);

    // Matrix_print(diff);

    // printf("Distance between u and v: %lf\n", Vector_distance(u, v));

    Matrix_print(Matrix_pow(m_pos, 10));


    return 0;
}