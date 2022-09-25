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

    Matrix_d *sq = get_square();

    Matrix_catch_d(&sq, Matrix_pow_d(sq, 3));
    Matrix_d *sq_3 = Matrix_from_d(
        (double[]) {10681.000000, 10490.000000, 11813.000000, 7830.000000, 11105.000000, 11420.000000, 7055.000000, 8967.000000, 6871.000000, 6046.000000, 7185.000000, 4899.000000, 6720.000000, 7045.000000, 3862.000000, 5637.000000, 7845.000000, 6869.000000, 7820.000000, 5215.000000, 7603.000000, 7571.000000, 4555.000000, 5906.000000, 11428.000000, 10243.000000, 11794.000000, 7442.000000, 10729.000000, 11454.000000, 6503.000000, 9057.000000, 12614.000000, 11574.000000, 13027.000000, 8291.000000, 12173.000000, 12708.000000, 7485.000000, 9773.000000, 9346.000000, 8532.000000, 10264.000000, 6262.000000, 9355.000000, 9328.000000, 5478.000000, 7607.000000, 9630.000000, 8960.000000, 10087.000000, 6510.000000, 9374.000000, 10434.000000, 5873.000000, 7757.000000, 10936.000000, 10037.000000, 11457.000000, 7264.000000, 10773.000000, 11155.000000, 6747.000000, 8662.000000},
        8, 8);

    assert(matcmp_d(sq, sq_3)); // Verify the matrix power computation.

    Matrix_free_d(sq);
    Matrix_free_d(sq_3);
}

void t_mat__det() {

    Matrix_d *s = get_square();
    assert(Matrix_det_d(s) == 5853640);
    Matrix_free_d(s);

    Matrix_d *id = Matrix_identity_d(3); // Anything higher than this and the complexity fucking explodes
    assert(Matrix_det_d(id) == 1.0);
    Matrix_free_d(id);
}

void t_mat_cdr_check() {

    ejovo_seed();

    Matrix_d *m1 = Matrix_rand_d(2, 2);
    Matrix_d *m2 = Matrix_rand_d(2, 2);

    Matrix_print_d(m1);
    Matrix_print_d(m2);

    printf("m2 c2 dot with m1 r 1: %lf\n", matcdr_check_d(m1, m2, 0, 1));

    Matrix_d *wide = get_wide();
    Matrix_d *sq = get_square();

    Matrix_free_d(wide);
    Matrix_free_d(sq);

    Matrix_free_d(m1);
    Matrix_free_d(m2);

}

void t_mat_mul() {

    Matrix_d *tall = get_tall();
    Matrix_d *sq = get_square();
    Matrix_d *sq_tall = Matrix_multiply_d(sq, tall);

    Matrix_d *true_value = Matrix_from_d(
        (double[]) {280.000000, 250.000000, 221.000000, 204.000000, 116.000000, 143.000000, 138.000000, 89.000000, 169.000000, 154.000000, 160.000000, 87.000000, 233.000000, 225.000000, 222.000000, 165.000000, 296.000000, 257.000000, 258.000000, 172.000000, 224.000000, 202.000000, 271.000000, 120.000000, 234.000000, 164.000000, 181.000000, 147.000000, 269.000000, 201.000000, 229.000000, 176.000000},
        8, 4);

    assert(matcmp_d(sq_tall, true_value));

    Matrix_free_d(tall);
    Matrix_free_d(sq);
    Matrix_free_d(sq_tall);
    Matrix_free_d(true_value);
}

void t_colnorm() {

    ejovo_seed();

    Matrix_d *m = Matrix_rand_d(5, 5);
    Matrix_print_d(m);
    printf("Colnorm: %lf\n", Matrix_col_norm_d(m, 3));

    Matrix_free_d(m);
}

void t_mat_normcol() {

    ejovo_seed();

    Matrix_d *m = Matrix_rand_d(5, 5);
    Matrix_print_d(m);
    Matrix_normalize_col_d(m, 3);
    Matrix_print_d(m);
    Matrix_normalize_cols_d(m);
    Matrix_print_d(m);

    Matrix_free_d(m);

}

void t_frobenius() {

    ejovo_seed();

    Matrix_d *m = Matrix_rand_d(5, 5);
    Matrix_print_d(m);
    printf("||m||_f = %lf\n", Matrix_frobenius_d(m));
    Matrix_free_d(m);

}

void t_mat_lu() {

    printf("Starting matlu\n");

    ejovo_seed();

    Matrix_d *m = Matrix_random_d(3, 3, 1, 10);
    Matrix_print_d(m);

    Matrix_d *U = Matrix_clone_d(m);

    printf("Matrix_d cloned\n");

    Matrix_d *L = matlu_nopivot_d(U);
    Matrix_print_d(L);
    Matrix_print_d(U);



    printf("L * U = \n");

    Matrix_print_d(Matrix_anon_d(Matrix_multiply_d(L, U)));

    Matrix_free_d(m);
    Matrix_free_d(U);
    Matrix_free_d(L);


    Matrix_d *A = Matrix_rand_d(3, 3);
    Vector_d*b = Vector_rand_d(3);

    Vector_d*x = Matrix_solve_lu_d(A, b);

    Matrix_print_d(A);
    Matrix_free_d(A);
    Matrix_free_d(b);
    Matrix_free_d(x);
    Matrix_anon_free_d();

}

void t_matrix_lu() {

    Matrix_d *m = Matrix_random_d(10, 10, 1, 12);

    LU_d lu = Matrix_lu_d(m);

    Matrix_print_d(m);
    printf("\n LU decomposition: \n");

    Matrix_print_d(lu.L);
    Matrix_print_d(lu.U);

    Matrix_free_d(lu.L);
    Matrix_free_d(lu.U);
    Matrix_free_d(m);

}

void t_jacobi() {

    printf("=============Jacobi iteration===================\n");

    Matrix_d *catch = NULL;

    ejovo_seed();
    // Matrix_d *A = Matrix_tridiagonal_d(15);
    // Matrix_d *A = Matrix_rand_d(3, 3);

    // wtf so my jacobi iteration works just fine when the b vector is the same....

    double data[] = {4, -1, 0, 1, 0, -1, 4, -1, 0, 1, 0, -1, 4, -1, 0, 1, 0, -1, 4, -1, 0, 1, 0, -1, 4}; // éléments de la matrice du livre, arrangé en ordre "row-major"

    Matrix_d *A = Matrix_from_d(data, 5, 5); // Créer une 5 x 5 matrice de data
    // Vector_d*b = Matrix_value_d(3, 1, 100); // creer b = [100, 100, 100, 100, 100]^T
    // Vector_d*b = Matrix_rand_d(15, 1); // creer b = [100, 100, 100, 100, 100]^T
    Vector_d*b = Matrix_rand_d(5, 1); // creer b = [100, 100, 100, 100, 100]^T

    // Vector_d*x = jacobi_iteration_d(A, b, Matrix_new_d(15, 1), 0.0001); // Tester l'algorithme avec x^0 = [0, 0, 0, 0, 0]^T, tolerance 0.0001
    Vector_d*x = jacobi_iteration_d(A, b, Matrix_catch_d(&catch, Matrix_new_d(5, 1)), 0.0001); // Tester l'algorithme avec x^0 = [0, 0, 0, 0, 0]^T, tolerance 0.0001

    // Afficher a l'écran les résultats
    printf("A: ");
    Matrix_print_d(A);
    // printf("b: ");
    // Matrix_print_d(b);
    printf("x: ");
    Matrix_print_d(x);

    Matrix_catch_d(&x, Matrix_solve_lu_d(A, b));
    printf("Exact solution: ");
    Matrix_print_d(x);

    // Matrix_set_d(A, 0, 2, 0);
    // Matrix_set_d(A, 2, 0, 0); // make matrix diagonal??

    // Vector_d*b = Matrix_value_d(24, 1, 500);
    // Vector_d*b = Matrix_rand_d(24, 1);

    // printf("Ax = ");
    // Matrix_print_d(Matrix_multiply_d(A, x));

    Matrix_free_d(A);
    Matrix_free_d(b);
    Matrix_free_d(x);
    Matrix_free_d(catch);
    // Matrix_d *B = Matrix_tridiagonal_d(10);
    // Matrix_print_d(B);
    // Matrix_free_d(B);


}

void t_vandermonde() {

    Matrix_d *v = Vector_runif_d(10, -3, 3);

    Matrix_print_d(v);

    Matrix_d *V = Matrix_vandermonde_d(v);

    Matrix_d *Vr = Matrix_vandermonde_reduced_d(v, 3);
    Matrix_d *Vr_t = Matrix_transpose_d(Vr);


    Matrix_print_d(V);
    Matrix_print_d(Vr);
    Matrix_print_d(Vr_t);

    Matrix_print_d(Matrix_anon_d(Matrix_multiply_d(Vr_t, Vr)));

    Matrix_anon_free_d();
    Matrix_reset_d(&V);
    Matrix_reset_d(&Vr);
    Matrix_reset_d(&Vr_t);
    Matrix_reset_d(&v);

    Matrix_d *r = ascol_d(range_d(1, 100, 24));

    Matrix_print_d(r);

    asrow_d(r);

    v = asrow_d(vector_d(5, 1.0, 13.0, -24.0, 14.0, 4.1));

    Matrix_print_d(v);

    Matrix_print_d(r);

    Matrix_free_d(v);
    Matrix_free_d(r);


}

void t_gausselim() {

    Matrix_d *A = Matrix_id_d(3, 3);
    Matrix_set_d(A, 1, 1, 2);
    Matrix_set_d(A, 1, 2, 2);
    Matrix_set_d(A, 1, 0, 3);
    Matrix_set_d(A, 0, 2, 5);

    Matrix_print_d(A);

    Matrix_d *b = Matrix_value_d(3, 1, 1);

    Matrix_d *x = gausselim_d(A, b);

    Matrix_print_d(x);

    Matrix_d *Ax = Matrix_multiply_d(A, x);

    Matrix_print_d(Ax);

    Matrix_reset_d(&A);
    Matrix_reset_d(&b);
    Matrix_reset_d(&x);
    Matrix_reset_d(&Ax);

}

void t_gausselim_rand() {

    Matrix_d *A = Matrix_random_d(5, 5, 1, 5);
    Matrix_d *b = Matrix_ones_d(5, 5);
    Matrix_d *x = gausselim_d(A, b);

    Matrix_d *Ax = Matrix_multiply_d(A, x);

    Matrix_print_d(Ax);

    Matrix_reset_d(&A);
    Matrix_reset_d(&b);
    Matrix_reset_d(&x);
    Matrix_reset_d(&Ax);

}

void t_inverse() {

    Matrix_d *not_square = Matrix_new_d(10, 5);

    assert(!Matrix_inverse_d(not_square));

    Matrix_d *id = Matrix_id_d(4, 4);
    Matrix_d *id_inv = Matrix_inverse_d(id);

    assert(matcmp_d(id, id_inv));

    // Curated so that |A| = 1
    Matrix_d *A = Matrix_from_d((double []) {8.0, 3.0, 5.0, 2.0}, 2, 2);
    Matrix_d *A_inv = Matrix_inverse_d(A);

    Matrix_d *A_true_inv = Matrix_from_d((double []) {2.0, -3.0, -5.0, 8.0}, 2, 2);

    assert(Matrix_det_d(A) == 1.0);
    assert(matcmp_d(A_inv, A_true_inv));

    Matrix_free_d(not_square);
    Matrix_free_d(id);
    Matrix_free_d(id_inv);
    Matrix_free_d(A);
    Matrix_free_d(A_inv);
    Matrix_free_d(A_true_inv);

}