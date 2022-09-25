#include "ejovo_matrix_generic.h"
#include "ejovo_print.h"
#include "assert.h"

int main(void) {

    // Matrix_d * A = Matrix_new_d(5, 5);

    Matrix_d * m1 = Matrix_ij_d(10, 10);
    Matrix_d * m2 = Matrix_ones_d(13, 3);
    Matrix_d * m3 = Matrix_new_d(3, 8);
    Matrix_d * m4 = Matrix_new_d(5, 5);

    assert(m1);
    assert(m2);
    assert(m3);
    assert(m4);

    Matrix_print_d(m1);
    Matrix_print_d(m2);
    Matrix_print_d(m3);
    Matrix_print_d(m4);

    print_line(80, '=');
    printf("Here begins the computational functions\n");
    print_line(80, '=');

    Matrix_reset_d(&m1);
    Matrix_reset_d(&m2);
    Matrix_reset_d(&m3);
    Matrix_reset_d(&m4);

    Matrix_d * m5 = Matrix_value_d(10, 10, 5);
    Matrix_d * m6 = Matrix_value_d(10, 10, 4);
    Matrix_d * m7 = Matrix_add_d(m5, m6);

    Matrix_print_d(m5);
    printf("\n\t+\n");
    Matrix_print_d(m6);
    printf("\n\t=\n");
    Matrix_print_d(m7);

    print_line(80, '=');
    ejovo_seed();


    Matrix_reset_d(&m5);
    Matrix_reset_d(&m6);
    Matrix_reset_d(&m7);

    Matrix_d * m8 = Matrix_random_d(6, 5, 0, 15);
    Matrix_d * m9 = Matrix_random_d(1, 6, 1, 2);
    Matrix_d * m10 = Matrix_multiply_d(m9, m8);
    assert(Matrix_comp_mult_d(m9, m8));
    assert(m10);



    Matrix_d * m11 = Matrix_random_d(5, 5, -5, 5);
    Matrix_print_d(m11);
    printf("\n\t^1 = \n");
    Matrix_print_d(Matrix_anon_d(Matrix_pow_d(m11, 1)));

    Matrix_d * m11_1 = Matrix_pow_d(m11, 1);
    Matrix_d * m11_1_0 = Matrix_pow_d(m11, 0);
    Matrix_d * m11_2 = Matrix_pow_d(m11, 2);
    Matrix_d * m11_4 = Matrix_pow_d(m11, 4);

    printf("\n\t^0 = \n");
    Matrix_print_d(Matrix_anon_d(Matrix_pow_d(m11_1, 0)));

    printf("\n\t^2 = \n");
    Matrix_print_d(m11_2);

    printf("\n\t^4 = \n");
    Matrix_print_d(m11_4);

    Matrix_print_d(m9);
    printf("\n\t*\n");
    Matrix_print_d(m8);
    printf("\n\t=\n");
    Matrix_print_d(m10);

    print_line(80, '-');



    Matrix_reset_d(&m8);
    Matrix_reset_d(&m9);
    Matrix_reset_d(&m10);

    Matrix_reset_d(&m11);
    Matrix_reset_d(&m11_1);
    Matrix_reset_d(&m11_1_0);
    Matrix_reset_d(&m11_2);
    Matrix_reset_d(&m11_4);

    Matrix_d * A1 = Matrix_rand_d(25, 25);
    Matrix_print_d(A1);
    printf("\n");

    Matrix_d * A_sub1 = Matrix_submat_d(A1, 0, 9, 0, 9); // get 10x10 block
    Matrix_d * A_sub2 = Matrix_submat_d(A1, 13, 22, 5, 14);
    Matrix_print_d(A_sub1);
    printf("\t+\n");
    Matrix_print_d(A_sub2);
    printf("\t=\n");
    Matrix_print_d(Matrix_anon_d(Matrix_add_d(A_sub1, A_sub2)));

    print_line(80, '&');

    Matrix_d * A_sub3 = Matrix_submat_d(A1, 0, 3, 3, 8);
    Matrix_d * A_sub4 = Matrix_submat_d(A1, 12, 15, 6, 14);

    Matrix_print_d(A_sub3);
    Matrix_print_d(A_sub4);
    Matrix_print_d(Matrix_anon_d(Matrix_ccat_d(A_sub3, A_sub4)));

    Matrix_d * A_sub5 = Matrix_submat_d(A1, 5, 8, 3, 8);
    Matrix_d * A_sub6 = Matrix_submat_d(A1, 12, 15, 6, 11);

    Matrix_print_d(A_sub5);
    Matrix_print_d(A_sub6);
    Matrix_print_d(Matrix_anon_d(Matrix_rcat_d(A_sub5, A_sub6))); // These are anonymous

    Matrix_d * A_sub0 = Matrix_submat_d(A1, 0, 0, 0, 0);
    Matrix_print_d(A_sub0);

    print_line(80, '#');

    Matrix_d * toy = Matrix_submat_d(A1, 4, 8, 8, 10); // 5 x 3 matrix
    Matrix_print_d(toy);

    // Matrix_d * toy_m00 = Matrix_minor_d(toy, 0, 0);
    // Matrix_print_d(toy_m00);

    // Matrix_d * toy_m42 = Matrix_minor_d(toy, 4, 2);
    // Matrix_print_d(toy_m42);

    // Matrix_d * toy_m40 = Matrix_minor_d(toy, 4, 0);
    // Matrix_print_d(toy_m40);

    // Matrix_d * toy_m02 = Matrix_minor_d(toy, 0, 2);
    // Matrix_print_d(toy_m02);

    // Matrix_d * toy_m10 = Matrix_minor_d(toy, 1, 0);
    // Matrix_print_d(toy_m10);

    // Matrix_d * toy_m30 = Matrix_minor_d(toy, 3, 0);
    // Matrix_print_d(toy_m30);

    Matrix_d * toy_m01 = Matrix_minor_d(toy, 0, 1);
    Matrix_print_d(toy_m01);

    Matrix_d * toy_m41 = Matrix_minor_d(toy, 4, 1);
    Matrix_print_d(toy_m41);

    Matrix_d * toy_m31 = Matrix_minor_d(toy, 3, 1);
    Matrix_print_d(toy_m31);

    print_line(80, '+');
    printf("\n Here starts the determinant tests\n");

    Matrix_d * D = Matrix_random_d(4, 4, 0, 3);
    Matrix_print_d(D);
    // printf("Det(D): %lf\n", Matrix_det_d(D));

    Matrix_reset_d(&A_sub0);
    Matrix_reset_d(&A_sub1);
    Matrix_reset_d(&A_sub2);
    Matrix_reset_d(&A_sub3);
    Matrix_reset_d(&A_sub4);
    Matrix_reset_d(&A_sub5);
    Matrix_reset_d(&A_sub6);

    Matrix_reset_d(&toy);
    Matrix_reset_d(&D);
    Matrix_reset_d(&A1);

    Matrix_reset_d(&toy_m01);
    Matrix_reset_d(&toy_m41);
    Matrix_reset_d(&toy_m31);

    Matrix_anon_free_d();

    return 0;
}