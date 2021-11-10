// test out these bad ass fucking iterator functions!!!

// I will also eventually want to benchmark these different function types

#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>


int main() {

    ejovo_seed();
    Matrix *m = Matrix_random(5, 5, 0, 10);

    printf("Starting matrix\n");
    Matrix_print(m);

    // test out the various array functions!

    RowIter *r0begin = Matrix_row_begin(m, 0);
    RowIter *r0col9 = matrowpos(m, 0, 9);

    printf("Adding 10 to m(1,:)\n");
    RowIter_apply_add_k(r0begin, r0col9, 10);

    RowIter *r0end = Matrix_row_end(m, 0);
    r0begin = matrowpos(m, 0, 3);

    printf("Multiplying m(1,4:) by 0\n");
    RowIter_apply_mult_k(r0begin, r0end, 0);

    // r0begin = matrowpos(m, 0, 0);
    RowIter *r2begin = Matrix_row_begin(m, 2);
    RowIter *r2end = Matrix_row_end(m, 2);

    printf("Subracting 100 from m(3,:)\n");
    RowIter_apply_sub_k(r2begin, r2end, 100);

    Matrix_print(m);

    RowIter *r5begin = Matrix_row_begin(m, 4);
    RowIter *r5end = Matrix_row_end(m, 4);

    printf("Dividing row 5 by 5\n");
    RowIter_apply_div_k(r5begin, r5end, 5);

    Matrix_print(m);

    printf("Matrix_at(0, 0) %lf\n", Matrix_at(m, 0, 0));
    printf("Matrix_at(4, 4) %lf\n", Matrix_at(m, 4, 4));


    printf("Adding row 3 to row 1\n");

    RowIter *r1begin = Matrix_row_begin(m, 0);
    RowIter *r1end = Matrix_row_end(m, 0);

    RowIter *r3begin = Matrix_row_begin(m, 3);

    RowIter_apply_add_iter(r1begin, r1end, r3begin);

    Matrix_print(m);


    return 0;
}