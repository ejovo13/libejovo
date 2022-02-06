#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

void t_mat_pow();
void t_mat_det();
void t_matcdr_check();
void t_matmul();
void t_colnorm();
void t_matnormcol();
void t_frobenius();
void t_matlu();
void t_Matrix_lu();
void t_jacobi();

// Not all of these function have been tested for accuracy.
// However, what is true is that none the the functions called in this test suite
// lead to any memory leaks (at least in their current state)

int main() {

    t_mat_pow();
    t_mat_det();
    t_matcdr_check();
    t_matmul();
    t_colnorm();
    t_matnormcol();
    t_frobenius();
    t_matlu();
    t_Matrix_lu();
    t_jacobi();

    return 0;
}

void t_mat_pow() {

    ejovo_seed();

    Matrix *m = Matrix_rand(10, 10);
    Matrix_print(m);
    Matrix_catch(&m, Matrix_pow(m, 3));
    Matrix_print(m);

    Matrix_free(m);

}

void t_mat_det() {

    ejovo_seed();

    Matrix *m = Matrix_rand(2, 2);
    Matrix_print(m);

    printf("Det(m): %lf\n", Matrix_det(m));

    Matrix_free(m);

}

void t_matcdr_check() {

    ejovo_seed();

    Matrix *m1 = Matrix_rand(2, 2);
    Matrix *m2 = Matrix_rand(2, 2);

    Matrix_print(m1);
    Matrix_print(m2);

    printf("m2 c2 dot with m1 r 1: %lf\n", matcdr_check(m1, m2, 0, 1));

    Matrix_free(m1);
    Matrix_free(m2);

}

void t_matmul() {

    ejovo_seed();

    Matrix *m1 = Matrix_rand(2, 2);
    Matrix *m2 = Matrix_rand(2, 2);

    Matrix_print(m1);
    Matrix_print(m2);

    Matrix *product = matmul(m1, m2);

    printf("m1 * m2 \n");

    Matrix_print(product);

    Matrix_free(product);
    Matrix_free(m1);
    Matrix_free(m2);


}

void t_colnorm() {

    ejovo_seed();

    Matrix *m = Matrix_rand(5, 5);
    Matrix_print(m);
    printf("Colnorm: %lf\n", Matrix_col_norm(m, 3));

    Matrix_free(m);


}

void t_matnormcol() {

    ejovo_seed();

    Matrix *m = Matrix_rand(5, 5);
    Matrix_print(m);
    Matrix_normalize_col(m, 3);
    Matrix_print(m);
    Matrix_normalize_cols(m);
    Matrix_print(m);

    Matrix_free(m);

}

void t_frobenius() {

    ejovo_seed();

    Matrix *m = Matrix_rand(5, 5);
    Matrix_print(m);
    printf("||m||_f = %lf\n", Matrix_frobenius(m));
    Matrix_free(m);

}

void t_matlu() {

    printf("Starting matlu\n");

    ejovo_seed();

    Matrix *m = Matrix_random(3, 3, 1, 10);
    Matrix_print(m);

    Matrix *U = Matrix_clone(m);

    printf("Matrix cloned\n");

    Matrix *L = matlu_nopivot(U);
    Matrix_print(L);
    Matrix_print(U);



    printf("L * U = \n");

    Matrix_print(Matrix_anon(Matrix_multiply(L, U)));

    Matrix_free(m);
    Matrix_free(U);
    Matrix_free(L);


    Matrix *A = Matrix_rand(3, 3);
    Vector *b = Vector_rand(3);

    Vector *x = Matrix_solve_lu(A, b);

    Matrix_print(A);
    Matrix_free(A);
    Matrix_free(b);
    Matrix_free(x);
    Matrix_anon_free();

}

void t_Matrix_lu() {

    Matrix *m = Matrix_random(10, 10, 1, 12);

    LU lu = Matrix_lu(m);

    Matrix_print(m);
    printf("\n LU decomposition: \n");

    Matrix_print(lu.L);
    Matrix_print(lu.U);

    Matrix_free(lu.L);
    Matrix_free(lu.U);
    Matrix_free(m);

}

void t_jacobi() {

    printf("=============Jacobi iteration===================\n");

    Matrix *catch = NULL;

    ejovo_seed();
    // Matrix *A = Matrix_tridiagonal(15);
    // Matrix *A = Matrix_rand(3, 3);

    // wtf so my jacobi iteration works just fine when the b vector is the same....

    double data[] = {4, -1, 0, 1, 0, -1, 4, -1, 0, 1, 0, -1, 4, -1, 0, 1, 0, -1, 4, -1, 0, 1, 0, -1, 4}; // éléments de la matrice du livre, arrangé en ordre "row-major"

    Matrix *A = Matrix_from(data, 5, 5); // Créer une 5 x 5 matrice de data
    // Vector *b = Matrix_value(3, 1, 100); // creer b = [100, 100, 100, 100, 100]^T
    // Vector *b = Matrix_rand(15, 1); // creer b = [100, 100, 100, 100, 100]^T
    Vector *b = Matrix_rand(5, 1); // creer b = [100, 100, 100, 100, 100]^T

    // Vector *x = jacobi_iteration(A, b, Matrix_new(15, 1), 0.0001); // Tester l'algorithme avec x^0 = [0, 0, 0, 0, 0]^T, tolerance 0.0001
    Vector *x = jacobi_iteration(A, b, Matrix_catch(&catch, Matrix_new(5, 1)), 0.0001); // Tester l'algorithme avec x^0 = [0, 0, 0, 0, 0]^T, tolerance 0.0001

    // Afficher a l'écran les résultats
    printf("A: ");
    Matrix_print(A);
    // printf("b: ");
    // Matrix_print(b);
    printf("x: ");
    Matrix_print(x);

    Matrix_catch(&x, Matrix_solve_lu(A, b));
    printf("Exact solution: ");
    Matrix_print(x);

    // Matrix_set(A, 0, 2, 0);
    // Matrix_set(A, 2, 0, 0); // make matrix diagonal??

    // Vector *b = Matrix_value(24, 1, 500);
    // Vector *b = Matrix_rand(24, 1);

    // printf("Ax = ");
    // Matrix_print(Matrix_multiply(A, x));

    Matrix_free(A);
    Matrix_free(b);
    Matrix_free(x);
    Matrix_free(catch);
    // Matrix *B = Matrix_tridiagonal(10);
    // Matrix_print(B);
    // Matrix_free(B);


}