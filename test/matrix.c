#include "ejovo_matrix.h"
#include "ejovo_print.h"
#include "assert.h"

int main(void) {

    // Matrix * A = Matrix_new(5, 5);

    Matrix * m1 = Matrix_ij(10, 10);
    Matrix * m2 = Matrix_ones(13, 3);
    Matrix * m3 = Matrix_new(3, 8);
    Matrix * m4 = Matrix_new(5, 5);

    assert(m1);
    assert(m2);
    assert(m3);
    assert(m4);

    Matrix_print(m1);
    Matrix_print(m2);
    Matrix_print(m3);
    Matrix_print(m4);

    print_line(80, '=');
    printf("Here begins the computational functions\n");
    print_line(80, '=');

    Matrix * m5 = Matrix_value(10, 10, 5);
    Matrix * m6 = Matrix_value(10, 10, 4);
    Matrix * m7 = Matrix_add(m5, m6);

    Matrix_print(m5);
    printf("\n\t+\n");
    Matrix_print(m6);
    printf("\n\t=\n");
    Matrix_print(m7);

    print_line(80, '=');
    ejovo_seed();

    Matrix * m8 = Matrix_random(6, 5, 0, 15);
    Matrix * m9 = Matrix_random(1, 6, 1, 2);
    Matrix * m10 = Matrix_multiply(m9, m8);
    assert(Matrix_comp_mult(m9, m8));
    assert(m10);


    Matrix * m11 = Matrix_random(5, 5, -5, 5);
    Matrix_print(m11);
    printf("\n\t^1 = \n");
    Matrix_print(Matrix_pow(m11, 1));

    Matrix * m11_1 = Matrix_pow(m11, 1);
    Matrix * m11_1_0 = Matrix_pow(m11, 0);
    Matrix * m11_2 = Matrix_pow(m11, 2);
    Matrix * m11_4 = Matrix_pow(m11, 4);

    printf("\n\t^0 = \n");
    Matrix_print(Matrix_pow(m11_1, 0));

    printf("\n\t^2 = \n");
    Matrix_print(m11_2);

    printf("\n\t^4 = \n");
    Matrix_print(m11_4);

    Matrix_print(m9);
    printf("\n\t*\n");
    Matrix_print(m8);
    printf("\n\t=\n");
    Matrix_print(m10);

    print_line(80, '-');

    Matrix * A1 = Matrix_rand(25, 25);
    Matrix_print(A1);
    printf("\n");

    Matrix * A_sub1 = Matrix_submat(A1, 0, 9, 0, 9); // get 10x10 block
    Matrix * A_sub2 = Matrix_submat(A1, 13, 22, 5, 14);
    Matrix_print(A_sub1);
    printf("\t+\n");
    Matrix_print(A_sub2);
    printf("\t=\n");
    Matrix_print(Matrix_add(A_sub1, A_sub2));

    print_line(80, '&');

    Matrix * A_sub3 = Matrix_submat(A1, 0, 3, 3, 8);
    Matrix * A_sub4 = Matrix_submat(A1, 12, 15, 6, 14);

    Matrix_print(A_sub3);
    Matrix_print(A_sub4);
    Matrix_print(Matrix_ccat(A_sub3, A_sub4));

    Matrix * A_sub5 = Matrix_submat(A1, 5, 8, 3, 8);
    Matrix * A_sub6 = Matrix_submat(A1, 12, 15, 6, 11);

    Matrix_print(A_sub5);
    Matrix_print(A_sub6);
    Matrix_print(Matrix_rcat(A_sub5, A_sub6));

    Matrix * A_sub0 = Matrix_submat(A1, 0, 0, 0, 0);
    Matrix_print(A_sub0);

    print_line(80, '#');

    Matrix * toy = Matrix_submat(A1, 4, 8, 8, 10); // 5 x 3 matrix
    Matrix_print(toy);

    // Matrix * toy_m00 = Matrix_minor(toy, 0, 0);
    // Matrix_print(toy_m00);

    // Matrix * toy_m42 = Matrix_minor(toy, 4, 2);
    // Matrix_print(toy_m42);

    // Matrix * toy_m40 = Matrix_minor(toy, 4, 0);
    // Matrix_print(toy_m40);

    // Matrix * toy_m02 = Matrix_minor(toy, 0, 2);
    // Matrix_print(toy_m02);

    // Matrix * toy_m10 = Matrix_minor(toy, 1, 0);
    // Matrix_print(toy_m10);

    // Matrix * toy_m30 = Matrix_minor(toy, 3, 0);
    // Matrix_print(toy_m30);

    Matrix * toy_m01 = Matrix_minor(toy, 0, 1);
    Matrix_print(toy_m01);

    Matrix * toy_m41 = Matrix_minor(toy, 4, 1);
    Matrix_print(toy_m41);

    Matrix * toy_m31 = Matrix_minor(toy, 3, 1);
    Matrix_print(toy_m31);

    print_line(80, "+");
    printf("\n Here starts the determinant tests\n");

    Matrix * D = Matrix_random(4, 4, 0, 3);
    Matrix_print(D);
    printf("Det(D): %lf\n", Matrix_det(D));




    return 0;
}