#include "ejovo_matrix.h"
#include "ejovo_print.h"
#include "assert.h"

int main(void) {

    // MATRIX_T * A = MATRIX_FN(new)(5, 5);

    MATRIX_T * m1 = MATRIX_FN(ij)(10, 10);
    MATRIX_T * m2 = MATRIX_FN(ones)(13, 3);
    MATRIX_T * m3 = MATRIX_FN(new)(3, 8);
    MATRIX_T * m4 = MATRIX_FN(new)(5, 5);

    assert(m1);
    assert(m2);
    assert(m3);
    assert(m4);

    MATRIX_FN(print)(m1);
    MATRIX_FN(print)(m2);
    MATRIX_FN(print)(m3);
    MATRIX_FN(print)(m4);

    print_line(80, '=');
    printf("Here begins the computational functions\n");
    print_line(80, '=');

    MATRIX_FN(reset)(&m1);
    MATRIX_FN(reset)(&m2);
    MATRIX_FN(reset)(&m3);
    MATRIX_FN(reset)(&m4);

    MATRIX_T * m5 = MATRIX_FN(value)(10, 10, 5);
    MATRIX_T * m6 = MATRIX_FN(value)(10, 10, 4);
    MATRIX_T * m7 = MATRIX_FN(add)(m5, m6);

    MATRIX_FN(print)(m5);
    printf("\n\t+\n");
    MATRIX_FN(print)(m6);
    printf("\n\t=\n");
    MATRIX_FN(print)(m7);

    print_line(80, '=');
    ejovo_seed();


    MATRIX_FN(reset)(&m5);
    MATRIX_FN(reset)(&m6);
    MATRIX_FN(reset)(&m7);

    MATRIX_T * m8 = MATRIX_FN(random)(6, 5, 0, 15);
    MATRIX_T * m9 = MATRIX_FN(random)(1, 6, 1, 2);
    MATRIX_T * m10 = MATRIX_FN(multiply)(m9, m8);
    assert(MATRIX_FN(comp_mult)(m9, m8));
    assert(m10);



    MATRIX_T * m11 = MATRIX_FN(random)(5, 5, -5, 5);
    MATRIX_FN(print)(m11);
    printf("\n\t^1 = \n");
    MATRIX_FN(print)(MATRIX_FN(anon)(MATRIX_FN(pow)(m11, 1)));

    MATRIX_T * m11_1 = MATRIX_FN(pow)(m11, 1);
    MATRIX_T * m11_1_0 = MATRIX_FN(pow)(m11, 0);
    MATRIX_T * m11_2 = MATRIX_FN(pow)(m11, 2);
    MATRIX_T * m11_4 = MATRIX_FN(pow)(m11, 4);

    printf("\n\t^0 = \n");
    MATRIX_FN(print)(MATRIX_FN(anon)(MATRIX_FN(pow)(m11_1, 0)));

    printf("\n\t^2 = \n");
    MATRIX_FN(print)(m11_2);

    printf("\n\t^4 = \n");
    MATRIX_FN(print)(m11_4);

    MATRIX_FN(print)(m9);
    printf("\n\t*\n");
    MATRIX_FN(print)(m8);
    printf("\n\t=\n");
    MATRIX_FN(print)(m10);

    print_line(80, '-');



    MATRIX_FN(reset)(&m8);
    MATRIX_FN(reset)(&m9);
    MATRIX_FN(reset)(&m10);

    MATRIX_FN(reset)(&m11);
    MATRIX_FN(reset)(&m11_1);
    MATRIX_FN(reset)(&m11_1_0);
    MATRIX_FN(reset)(&m11_2);
    MATRIX_FN(reset)(&m11_4);

    MATRIX_T * A1 = MATRIX_FN(rand)(25, 25);
    MATRIX_FN(print)(A1);
    printf("\n");

    MATRIX_T * A_sub1 = MATRIX_FN(submat)(A1, 0, 9, 0, 9); // get 10x10 block
    MATRIX_T * A_sub2 = MATRIX_FN(submat)(A1, 13, 22, 5, 14);
    MATRIX_FN(print)(A_sub1);
    printf("\t+\n");
    MATRIX_FN(print)(A_sub2);
    printf("\t=\n");
    MATRIX_FN(print)(MATRIX_FN(anon)(MATRIX_FN(add)(A_sub1, A_sub2)));

    print_line(80, '&');

    MATRIX_T * A_sub3 = MATRIX_FN(submat)(A1, 0, 3, 3, 8);
    MATRIX_T * A_sub4 = MATRIX_FN(submat)(A1, 12, 15, 6, 14);

    MATRIX_FN(print)(A_sub3);
    MATRIX_FN(print)(A_sub4);
    MATRIX_FN(print)(MATRIX_FN(anon)(MATRIX_FN(ccat)(A_sub3, A_sub4)));

    MATRIX_T * A_sub5 = MATRIX_FN(submat)(A1, 5, 8, 3, 8);
    MATRIX_T * A_sub6 = MATRIX_FN(submat)(A1, 12, 15, 6, 11);

    MATRIX_FN(print)(A_sub5);
    MATRIX_FN(print)(A_sub6);
    MATRIX_FN(print)(MATRIX_FN(anon)(MATRIX_FN(rcat)(A_sub5, A_sub6))); // These are anonymous

    MATRIX_T * A_sub0 = MATRIX_FN(submat)(A1, 0, 0, 0, 0);
    MATRIX_FN(print)(A_sub0);

    print_line(80, '#');

    MATRIX_T * toy = MATRIX_FN(submat)(A1, 4, 8, 8, 10); // 5 x 3 matrix
    MATRIX_FN(print)(toy);

    // MATRIX_T * toy_m00 = MATRIX_FN(minor)(toy, 0, 0);
    // MATRIX_FN(print)(toy_m00);

    // MATRIX_T * toy_m42 = MATRIX_FN(minor)(toy, 4, 2);
    // MATRIX_FN(print)(toy_m42);

    // MATRIX_T * toy_m40 = MATRIX_FN(minor)(toy, 4, 0);
    // MATRIX_FN(print)(toy_m40);

    // MATRIX_T * toy_m02 = MATRIX_FN(minor)(toy, 0, 2);
    // MATRIX_FN(print)(toy_m02);

    // MATRIX_T * toy_m10 = MATRIX_FN(minor)(toy, 1, 0);
    // MATRIX_FN(print)(toy_m10);

    // MATRIX_T * toy_m30 = MATRIX_FN(minor)(toy, 3, 0);
    // MATRIX_FN(print)(toy_m30);

    MATRIX_T * toy_m01 = MATRIX_FN(minor)(toy, 0, 1);
    MATRIX_FN(print)(toy_m01);

    MATRIX_T * toy_m41 = MATRIX_FN(minor)(toy, 4, 1);
    MATRIX_FN(print)(toy_m41);

    MATRIX_T * toy_m31 = MATRIX_FN(minor)(toy, 3, 1);
    MATRIX_FN(print)(toy_m31);

    print_line(80, '+');
    printf("\n Here starts the determinant tests\n");

    MATRIX_T * D = MATRIX_FN(random)(4, 4, 0, 3);
    MATRIX_FN(print)(D);
    // printf("Det(D): %lf\n", MATRIX_FN(det)(D));

    MATRIX_FN(reset)(&A_sub0);
    MATRIX_FN(reset)(&A_sub1);
    MATRIX_FN(reset)(&A_sub2);
    MATRIX_FN(reset)(&A_sub3);
    MATRIX_FN(reset)(&A_sub4);
    MATRIX_FN(reset)(&A_sub5);
    MATRIX_FN(reset)(&A_sub6);

    MATRIX_FN(reset)(&toy);
    MATRIX_FN(reset)(&D);
    MATRIX_FN(reset)(&A1);

    MATRIX_FN(reset)(&toy_m01);
    MATRIX_FN(reset)(&toy_m41);
    MATRIX_FN(reset)(&toy_m31);

    MATRIX_FN(anon_free)();

    return 0;
}