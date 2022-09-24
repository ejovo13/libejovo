#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

// We want to make sure that none of the core algorithms are introducting memory leaks
void t_mat_alloc();
void t_mat_clone();
void t_mat_catch();
void t_vector_linspace();



int main() {

    t_mat_alloc();
    // t_mat_clone();
    // t_mat_catch();
    // t_vector_linspace();



    return 0;
}

void t_mat_alloc() {

    MATRIX_T *m = MAT_FN(alloc)(10, 10);

    assert(m);
    assert(m->data);
    assert(m->ncols == 10);
    assert(m->nrows == 10);
    // Matrices allocated with matalloc should NOT be used.
    // This is because the values are uninitialized


    MATRIX_FN(set)(m, 5, 5, 100);
    // MATRIX_FN(print)(m);
    MATRIX_FN(reset)(&m);
    MATRIX_FN(free)(m);
    printf("Should be null: %x\n", m);
    MATRIX_FN(reset)(&m);

}

void t_mat_clone() {

    ejovo_seed();

    MATRIX_T *m = MATRIX_FN(rand)(5, 5);
    MATRIX_T *m_clone = MAT_FN(clone)(m);

    MATRIX_FN(reset)(&m);
    MATRIX_FN(free)(m_clone);


}

void t_mat_catch() {

    ejovo_seed();

    MATRIX_T *m = MATRIX_FN(rand)(10, 10);
    MATRIX_T *m1 = NULL;
    MATRIX_FN(catch)(&m1, MAT_FN(clone)(m));
    MATRIX_FN(catch)(&m1, MATRIX_FN(add)(m, m1));

    MATRIX_FN(free)(m);
    MATRIX_FN(free)(m1);

}

void t_vector_linspace() {

    Vector *v = VECTOR_FN(linspace)(1, 0, 4);
    assert(VECTOR_FN(first)(v) == 1);

    MATRIX_FN(print)(v);

    assert(VECTOR_FN(last)(v) == 0);

    MATRIX_FN(reset)(&v);


}