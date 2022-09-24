#include "test_mat.h"

void t_mat__pow();
void t_mat__det();
void t_mat_cdr_check();
void t_mat_mul();
void t_colnorm();
void t_mat_normcol();
void t_frobenius();
void t_mat_lu();
void t_matrix_lu();
void t_jacobi();
void t_vandermonde();
void t_gausselim();
void t_gausselim_rand();
void t_inverse();

// Not all of these function have been tested for accuracy.
// However, what is true is that none the the functions called in this test suite
// lead to any memory leaks (at least in their current state)

// TODO
// - [] Use assert on the remaining random functions

int main() {

    ejovo_seed();

    t_mat__pow();
    t_mat__det();
    t_mat_cdr_check();
    t_mat_mul();
    t_colnorm();
    t_mat_normcol();
    t_frobenius();
    t_mat_lu();
    t_matrix_lu();
    t_jacobi();
    t_vandermonde();
    t_gausselim();
    t_gausselim_rand();
    t_inverse();

    return 0;
}

void t_mat__pow() {

    MATRIX_T *sq = get_square();

    MATRIX_FN(catch)(&sq, MATRIX_FN(pow)(sq, 3));
    MATRIX_T *sq_3 = MATRIX_FN(from)(
        (double[]) {10681.000000, 10490.000000, 11813.000000, 7830.000000, 11105.000000, 11420.000000, 7055.000000, 8967.000000, 6871.000000, 6046.000000, 7185.000000, 4899.000000, 6720.000000, 7045.000000, 3862.000000, 5637.000000, 7845.000000, 6869.000000, 7820.000000, 5215.000000, 7603.000000, 7571.000000, 4555.000000, 5906.000000, 11428.000000, 10243.000000, 11794.000000, 7442.000000, 10729.000000, 11454.000000, 6503.000000, 9057.000000, 12614.000000, 11574.000000, 13027.000000, 8291.000000, 12173.000000, 12708.000000, 7485.000000, 9773.000000, 9346.000000, 8532.000000, 10264.000000, 6262.000000, 9355.000000, 9328.000000, 5478.000000, 7607.000000, 9630.000000, 8960.000000, 10087.000000, 6510.000000, 9374.000000, 10434.000000, 5873.000000, 7757.000000, 10936.000000, 10037.000000, 11457.000000, 7264.000000, 10773.000000, 11155.000000, 6747.000000, 8662.000000},
        8, 8);

    assert(MAT_FN(cmp)(sq, sq_3)); // Verify the matrix power computation.

    MATRIX_FN(free)(sq);
    MATRIX_FN(free)(sq_3);
}

void t_mat__det() {

    MATRIX_T *s = get_square();
    assert(MATRIX_FN(det)(s) == 5853640);
    MATRIX_FN(free)(s);

    MATRIX_T *id = MATRIX_FN(identity)(3); // Anything higher than this and the complexity fucking explodes
    assert(MATRIX_FN(det)(id) == 1.0);
    MATRIX_FN(free)(id);
}

void t_mat_cdr_check() {

    ejovo_seed();

    MATRIX_T *m1 = MATRIX_FN(rand)(2, 2);
    MATRIX_T *m2 = MATRIX_FN(rand)(2, 2);

    MATRIX_FN(print)(m1);
    MATRIX_FN(print)(m2);

    printf("m2 c2 dot with m1 r 1: %lf\n", MAT_FN(cdr_check)(m1, m2, 0, 1));

    MATRIX_T *wide = get_wide();
    MATRIX_T *sq = get_square();

    MATRIX_FN(free)(wide);
    MATRIX_FN(free)(sq);

    MATRIX_FN(free)(m1);
    MATRIX_FN(free)(m2);

}

void t_mat_mul() {

    MATRIX_T *tall = get_tall();
    MATRIX_T *sq = get_square();
    MATRIX_T *sq_tall = MATRIX_FN(multiply)(sq, tall);

    MATRIX_T *true_value = MATRIX_FN(from)(
        (double[]) {280.000000, 250.000000, 221.000000, 204.000000, 116.000000, 143.000000, 138.000000, 89.000000, 169.000000, 154.000000, 160.000000, 87.000000, 233.000000, 225.000000, 222.000000, 165.000000, 296.000000, 257.000000, 258.000000, 172.000000, 224.000000, 202.000000, 271.000000, 120.000000, 234.000000, 164.000000, 181.000000, 147.000000, 269.000000, 201.000000, 229.000000, 176.000000},
        8, 4);

    assert(MAT_FN(cmp)(sq_tall, true_value));

    MATRIX_FN(free)(tall);
    MATRIX_FN(free)(sq);
    MATRIX_FN(free)(sq_tall);
    MATRIX_FN(free)(true_value);
}

void t_colnorm() {

    ejovo_seed();

    MATRIX_T *m = MATRIX_FN(rand)(5, 5);
    MATRIX_FN(print)(m);
    printf("Colnorm: %lf\n", MATRIX_FN(col_norm)(m, 3));

    MATRIX_FN(free)(m);
}

void t_mat_normcol() {

    ejovo_seed();

    MATRIX_T *m = MATRIX_FN(rand)(5, 5);
    MATRIX_FN(print)(m);
    MATRIX_FN(normalize_col)(m, 3);
    MATRIX_FN(print)(m);
    MATRIX_FN(normalize_cols)(m);
    MATRIX_FN(print)(m);

    MATRIX_FN(free)(m);

}

void t_frobenius() {

    ejovo_seed();

    MATRIX_T *m = MATRIX_FN(rand)(5, 5);
    MATRIX_FN(print)(m);
    printf("||m||_f = %lf\n", MATRIX_FN(frobenius)(m));
    MATRIX_FN(free)(m);

}

void t_mat_lu() {

    printf("Starting matlu\n");

    ejovo_seed();

    MATRIX_T *m = MATRIX_FN(random)(3, 3, 1, 10);
    MATRIX_FN(print)(m);

    MATRIX_T *U = MATRIX_FN(clone)(m);

    printf("MATRIX_T cloned\n");

    MATRIX_T *L = MAT_FN(lu_nopivot)(U);
    MATRIX_FN(print)(L);
    MATRIX_FN(print)(U);



    printf("L * U = \n");

    MATRIX_FN(print)(MATRIX_FN(anon)(MATRIX_FN(multiply)(L, U)));

    MATRIX_FN(free)(m);
    MATRIX_FN(free)(U);
    MATRIX_FN(free)(L);


    MATRIX_T *A = MATRIX_FN(rand)(3, 3);
    Vector *b = VECTOR_FN(rand)(3);

    Vector *x = MATRIX_FN(solve_lu)(A, b);

    MATRIX_FN(print)(A);
    MATRIX_FN(free)(A);
    MATRIX_FN(free)(b);
    MATRIX_FN(free)(x);
    MATRIX_FN(anon_free)();

}

void t_matrix_lu() {

    MATRIX_T *m = MATRIX_FN(random)(10, 10, 1, 12);

    LU lu = MATRIX_FN(lu)(m);

    MATRIX_FN(print)(m);
    printf("\n LU decomposition: \n");

    MATRIX_FN(print)(lu.L);
    MATRIX_FN(print)(lu.U);

    MATRIX_FN(free)(lu.L);
    MATRIX_FN(free)(lu.U);
    MATRIX_FN(free)(m);

}

void t_jacobi() {

    printf("=============Jacobi iteration===================\n");

    MATRIX_T *catch = NULL;

    ejovo_seed();
    // MATRIX_T *A = MATRIX_FN(tridiagonal)(15);
    // MATRIX_T *A = MATRIX_FN(rand)(3, 3);

    // wtf so my jacobi iteration works just fine when the b vector is the same....

    double data[] = {4, -1, 0, 1, 0, -1, 4, -1, 0, 1, 0, -1, 4, -1, 0, 1, 0, -1, 4, -1, 0, 1, 0, -1, 4}; // éléments de la matrice du livre, arrangé en ordre "row-major"

    MATRIX_T *A = MATRIX_FN(from)(data, 5, 5); // Créer une 5 x 5 matrice de data
    // Vector *b = MATRIX_FN(value)(3, 1, 100); // creer b = [100, 100, 100, 100, 100]^T
    // Vector *b = MATRIX_FN(rand)(15, 1); // creer b = [100, 100, 100, 100, 100]^T
    Vector *b = MATRIX_FN(rand)(5, 1); // creer b = [100, 100, 100, 100, 100]^T

    // Vector *x = jacobi_iteration(A, b, MATRIX_FN(new)(15, 1), 0.0001); // Tester l'algorithme avec x^0 = [0, 0, 0, 0, 0]^T, tolerance 0.0001
    Vector *x = jacobi_iteration(A, b, MATRIX_FN(catch)(&catch, MATRIX_FN(new)(5, 1)), 0.0001); // Tester l'algorithme avec x^0 = [0, 0, 0, 0, 0]^T, tolerance 0.0001

    // Afficher a l'écran les résultats
    printf("A: ");
    MATRIX_FN(print)(A);
    // printf("b: ");
    // MATRIX_FN(print)(b);
    printf("x: ");
    MATRIX_FN(print)(x);

    MATRIX_FN(catch)(&x, MATRIX_FN(solve_lu)(A, b));
    printf("Exact solution: ");
    MATRIX_FN(print)(x);

    // MATRIX_FN(set)(A, 0, 2, 0);
    // MATRIX_FN(set)(A, 2, 0, 0); // make matrix diagonal??

    // Vector *b = MATRIX_FN(value)(24, 1, 500);
    // Vector *b = MATRIX_FN(rand)(24, 1);

    // printf("Ax = ");
    // MATRIX_FN(print)(MATRIX_FN(multiply)(A, x));

    MATRIX_FN(free)(A);
    MATRIX_FN(free)(b);
    MATRIX_FN(free)(x);
    MATRIX_FN(free)(catch);
    // MATRIX_T *B = MATRIX_FN(tridiagonal)(10);
    // MATRIX_FN(print)(B);
    // MATRIX_FN(free)(B);


}

void t_vandermonde() {

    MATRIX_T *v = VECTOR_FN(runif)(10, -3, 3);

    MATRIX_FN(print)(v);

    MATRIX_T *V = MATRIX_FN(vandermonde)(v);

    MATRIX_T *Vr = MATRIX_FN(vandermonde_reduced)(v, 3);
    MATRIX_T *Vr_t = MATRIX_FN(transpose)(Vr);


    MATRIX_FN(print)(V);
    MATRIX_FN(print)(Vr);
    MATRIX_FN(print)(Vr_t);

    MATRIX_FN(print)(MATRIX_FN(anon)(MATRIX_FN(multiply)(Vr_t, Vr)));

    MATRIX_FN(anon_free)();
    MATRIX_FN(reset)(&V);
    MATRIX_FN(reset)(&Vr);
    MATRIX_FN(reset)(&Vr_t);
    MATRIX_FN(reset)(&v);

    MATRIX_T *r = ascol(range(1, 100, 24));

    MATRIX_FN(print)(r);

    asrow(r);

    v = asrow(vector(5, 1.0, 13.0, -24.0, 14.0, 4.1));

    MATRIX_FN(print)(v);

    MATRIX_FN(print)(r);

    MATRIX_FN(free)(v);
    MATRIX_FN(free)(r);


}

void t_gausselim() {

    MATRIX_T *A = MATRIX_FN(id)(3, 3);
    MATRIX_FN(set)(A, 1, 1, 2);
    MATRIX_FN(set)(A, 1, 2, 2);
    MATRIX_FN(set)(A, 1, 0, 3);
    MATRIX_FN(set)(A, 0, 2, 5);

    MATRIX_FN(print)(A);

    MATRIX_T *b = MATRIX_FN(value)(3, 1, 1);

    MATRIX_T *x = gausselim(A, b);

    MATRIX_FN(print)(x);

    MATRIX_T *Ax = MATRIX_FN(multiply)(A, x);

    MATRIX_FN(print)(Ax);

    MATRIX_FN(reset)(&A);
    MATRIX_FN(reset)(&b);
    MATRIX_FN(reset)(&x);
    MATRIX_FN(reset)(&Ax);

}

void t_gausselim_rand() {

    MATRIX_T *A = MATRIX_FN(random)(5, 5, 1, 5);
    MATRIX_T *b = MATRIX_FN(ones)(5, 5);
    MATRIX_T *x = gausselim(A, b);

    MATRIX_T *Ax = MATRIX_FN(multiply)(A, x);

    MATRIX_FN(print)(Ax);

    MATRIX_FN(reset)(&A);
    MATRIX_FN(reset)(&b);
    MATRIX_FN(reset)(&x);
    MATRIX_FN(reset)(&Ax);

}

void t_inverse() {

    MATRIX_T *not_square = MATRIX_FN(new)(10, 5);

    assert(!MATRIX_FN(inverse)(not_square));

    MATRIX_T *id = MATRIX_FN(id)(4, 4);
    MATRIX_T *id_inv = MATRIX_FN(inverse)(id);

    assert(MAT_FN(cmp)(id, id_inv));

    // Curated so that |A| = 1
    MATRIX_T *A = MATRIX_FN(from)((double []) {8.0, 3.0, 5.0, 2.0}, 2, 2);
    MATRIX_T *A_inv = MATRIX_FN(inverse)(A);

    MATRIX_T *A_true_inv = MATRIX_FN(from)((double []) {2.0, -3.0, -5.0, 8.0}, 2, 2);

    assert(MATRIX_FN(det)(A) == 1.0);
    assert(MAT_FN(cmp)(A_inv, A_true_inv));

    MATRIX_FN(free)(not_square);
    MATRIX_FN(free)(id);
    MATRIX_FN(free)(id_inv);
    MATRIX_FN(free)(A);
    MATRIX_FN(free)(A_inv);
    MATRIX_FN(free)(A_true_inv);

}