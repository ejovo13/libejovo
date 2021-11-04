// test routines to copy matrices elementwise and bitewise

#include "ejovo_matrix.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int main() {

    ejovo_seed();
    Matrix *m = Matrix_rand(10, 10);

    Matrix_print(m);

    Matrix *m_copy = Matrix_clone(m);

    Matrix_print(m_copy);

    assert(matcmp(m, m_copy));
    assert(matcmp_loop(m, m_copy));
    assert(matcmp_bytes(m, m_copy));

    Matrix_set(m_copy, 4, 4, 10.3);

    assert(!matcmp(m, m_copy));
    assert(!matcmp_loop(m, m_copy));
    assert(!matcmp_bytes(m, m_copy));




    return 0;
}