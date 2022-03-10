#include "test_mat.h"

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
void t_vandermonde();

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
    t_vandermonde();

    return 0;
}

void t_mat_pow() {

    Matrix *sq = get_square();

    Matrix_catch(&sq, Matrix_pow(sq, 3));
    Matrix *sq_3 = Matrix_from(
        (double[]) {10681.000000, 10490.000000, 11813.000000, 7830.000000, 11105.000000, 11420.000000, 7055.000000, 8967.000000, 6871.000000, 6046.000000, 7185.000000, 4899.000000, 6720.000000, 7045.000000, 3862.000000, 5637.000000, 7845.000000, 6869.000000, 7820.000000, 5215.000000, 7603.000000, 7571.000000, 4555.000000, 5906.000000, 11428.000000, 10243.000000, 11794.000000, 7442.000000, 10729.000000, 11454.000000, 6503.000000, 9057.000000, 12614.000000, 11574.000000, 13027.000000, 8291.000000, 12173.000000, 12708.000000, 7485.000000, 9773.000000, 9346.000000, 8532.000000, 10264.000000, 6262.000000, 9355.000000, 9328.000000, 5478.000000, 7607.000000, 9630.000000, 8960.000000, 10087.000000, 6510.000000, 9374.000000, 10434.000000, 5873.000000, 7757.000000, 10936.000000, 10037.000000, 11457.000000, 7264.000000, 10773.000000, 11155.000000, 6747.000000, 8662.000000},
        8, 8);

    assert(matcmp(sq, sq_3)); // Verify the matrix power computation.

    Matrix_free(sq);
    Matrix_free(sq_3);
}

void t_mat_det() {

    Matrix *s = get_square();
    assert(Matrix_det(s) == 5853640);
    Matrix_free(s);
}

void t_matcdr_check() {

    ejovo_seed();

    Matrix *m1 = Matrix_rand(2, 2);
    Matrix *m2 = Matrix_rand(2, 2);

    Matrix_print(m1);
    Matrix_print(m2);

    printf("m2 c2 dot with m1 r 1: %lf\n", matcdr_check(m1, m2, 0, 1));

    Matrix *wide = get_wide();
    Matrix *sq = get_square();

    Matrix_free(wide);
    Matrix_free(sq);

    Matrix_free(m1);
    Matrix_free(m2);

}

void t_matmul() {

    Matrix *tall = get_tall();
    Matrix *sq = get_square();
    Matrix *sq_tall = Matrix_multiply(sq, tall);

    Matrix *true_value = Matrix_from(
        (double[]) {280.000000, 250.000000, 221.000000, 204.000000, 116.000000, 143.000000, 138.000000, 89.000000, 169.000000, 154.000000, 160.000000, 87.000000, 233.000000, 225.000000, 222.000000, 165.000000, 296.000000, 257.000000, 258.000000, 172.000000, 224.000000, 202.000000, 271.000000, 120.000000, 234.000000, 164.000000, 181.000000, 147.000000, 269.000000, 201.000000, 229.000000, 176.000000},
        8, 4);

    assert(matcmp(sq_tall, true_value));

    Matrix_free(tall);
    Matrix_free(sq);
    Matrix_free(sq_tall);
    Matrix_free(true_value);
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

void t_vandermonde() {

    Matrix *v = Vector_runif(10, -3, 3);

    Matrix_print(v);

    Matrix *V = Matrix_vandermonde(v);

    Matrix *Vr = Matrix_vandermonde_reduced(v, 3);
    Matrix *Vr_t = Matrix_transpose(Vr);


    Matrix_print(V);
    Matrix_print(Vr);
    Matrix_print(Vr_t);

    Matrix_print(Matrix_anon(Matrix_multiply(Vr_t, Vr)));

    Matrix_anon_free();
    Matrix_reset(&V);
    Matrix_reset(&Vr);
    Matrix_reset(&Vr_t);

    Matrix *r = ascol(range(1, 100, 24));

    Matrix_print(r);

    asrow(r);

    v = asrow(vector(5, 1.0, 13.0, -24.0, 14.0, 4.1));

    Matrix_print(v);

    Matrix_print(r);


}