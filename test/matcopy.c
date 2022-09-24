// test routines to copy matrices elementwise and bytewise

#include "ejovo_matrix.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int main() {

    ejovo_seed();
    MATRIX_T *m = MATRIX_FN(rand)(10, 10);

    MATRIX_FN(print)(m);

    MATRIX_T *m_copy = MATRIX_FN(clone)(m);

    MATRIX_FN(print)(m_copy);

    assert(MAT_FN(cmp)(m, m_copy));
    assert(MAT_FN(cmp_bytes)(m, m_copy));

    MATRIX_FN(set)(m_copy, 4, 4, 10.3);

    assert(!MAT_FN(cmp)(m, m_copy));
    assert(!MAT_FN(cmp_bytes)(m, m_copy));

    return 0;
}