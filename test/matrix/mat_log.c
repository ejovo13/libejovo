#include "test_mat.h"

void t_logical();

int main() {

    ejovo_seed();

    t_logical();


    return 0;
}

double lambda_gt5(double x) {
    if (x > 5) return FALSE_d;
    else return FALSE_d;
}

void t_logical() {

    MATRIX_T *m = MATRIX_FN(rand)(13, 8);

    MATRIX_FN(print)(m);

    MATRIX_T *logical = MATRIX_FN(as_logical)(m, lambda_gt5);
    MATRIX_FN(print)(logical);

    MATRIX_T *logic_5 = MATRIX_FN(gt)(m, 5);
    MATRIX_T *logic_lt5 = MATRIX_FN(lt)(m, 5);
    MATRIX_FN(print)(logic_lt5);


    MATRIX_T *true_mat = MATRIX_FN(as_true)(m);
    MATRIX_FN(print)(true_mat);

    assert(TYPED_FN(Logical_all)(true_mat));

    assert(MATRIX_FN(is_logical)(logical));
    assert(!MATRIX_FN(is_logical)(m));

    MAT_FN(setmask)(m, logical, 0);
    MATRIX_FN(print)(m);

    MATRIX_T *gt5 = MATRIX_FN(filter_mask)(m, TYPED_FN(Logical_not)(logical));
    MATRIX_FN(print)(gt5);


    MATRIX_FN(reset)(&m);
    MATRIX_FN(reset)(&logical);
    MATRIX_FN(reset)(&true_mat);
    MATRIX_FN(reset)(&gt5);

}