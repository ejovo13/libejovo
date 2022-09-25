// test routines to copy matrices elementwise and bytewise

#include "ejovo_matrix_generic.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int main() {

    ejovo_seed();
    Matrix_d *m = Matrix_rand_d(10, 10);

    Matrix_print_d(m);

    Matrix_d *m_copy = Matrix_clone_d(m);

    Matrix_print_d(m_copy);

    assert(matcmp_d(m, m_copy));
    assert(matcmp_bytes_d(m, m_copy));

    Matrix_set_d(m_copy, 4, 4, 10.3);

    assert(!matcmp_d(m, m_copy));
    assert(!matcmp_bytes_d(m, m_copy));

    return 0;
}