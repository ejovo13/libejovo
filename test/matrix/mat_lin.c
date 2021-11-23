#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

void t_matlu();
void t_Matrix_lu();
void t_jacobi();

int main() {

    t_matlu();
    t_Matrix_lu();
    t_jacobi();


    return 0;
}

void t_matlu() {

    ejovo_seed();

    Matrix *m = Matrix_random(3, 3, 1, 10);
    Matrix_print(m);

    Matrix *U = Matrix_clone(m);

    Matrix *L = matlu_nopivot(U);
    Matrix_print(L);
    Matrix_print(U);

    printf("L * U = \n");

    Matrix_print(Matrix_multiply(L, U));

}

void t_Matrix_lu() {

    Matrix *m = Matrix_random(10, 10, 1, 12);

    LU lu = Matrix_lu(m);

    Matrix_print(m);
    printf("\n LU decomposition: \n");

    Matrix_print(lu.L);
    Matrix_print(lu.U);

}

void t_jacobi() {

    printf("=============Jacobi iteration===================\n");

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
    Vector *x = jacobi_iteration(A, b, Matrix_new(5, 1), 0.0001); // Tester l'algorithme avec x^0 = [0, 0, 0, 0, 0]^T, tolerance 0.0001

    // Afficher a l'écran les résultats
    printf("A: ");
    Matrix_print(A);
    // printf("b: ");
    // Matrix_print(b);
    printf("x: ");
    Matrix_print(x);

    x = Matrix_solve_lu(A, b);
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
    // Matrix *B = Matrix_tridiagonal(10);
    // Matrix_print(B);
    // Matrix_free(B);


}