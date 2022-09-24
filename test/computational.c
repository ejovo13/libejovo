#include "ejovo_matrix_generic.h"
#include <assert.h>
#include <stdbool.h>


int main() {

    printf("Sup bitch\n");

    MATRIX_T *K = MATRIX_FN(K)(2);
    MATRIX_FN(print)(K);
    MATRIX_FN(free)(K);

    MATRIX_T *K5 = MATRIX_FN(K)(5);
    MATRIX_FN(print)(K);

    MATRIX_T *K15 = MATRIX_FN(K)(15);
    MATRIX_FN(print)(K15);

    MATRIX_T *C5 = MATRIX_FN(C)(5);
    MATRIX_FN(print)(C5);

    MATRIX_T *T5 = MATRIX_FN(T)(5);
    MATRIX_FN(print)(T5);

    MATRIX_T *B5 = MATRIX_FN(B)(5);
    MATRIX_FN(print)(B5);

    MATRIX_FN(free)(K5);
    MATRIX_FN(free)(K15);
    MATRIX_FN(free)(C5);
    MATRIX_FN(free)(T5);
    MATRIX_FN(free)(B5);


    return 0;
}