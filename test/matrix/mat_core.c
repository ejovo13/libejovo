#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

// We want to make sure that none of the core algorithms are introducting memory leaks
void t_matalloc();
void t_matclone();
void t_matcatch();
void t_vector_linspace();



int main() {

    t_matalloc();
    // t_matclone();
    // t_matcatch();
    // t_vector_linspace();



    return 0;
}

void t_matalloc() {

    Matrix *m = matalloc(10, 10);

    assert(m);
    assert(m->data);
    assert(m->ncols == 10);
    assert(m->nrows == 10);
    // Matrices allocated with matalloc should NOT be used.
    // This is because the values are uninitialized


    Matrix_set(m, 5, 5, 100);
    // Matrix_print(m);
    Matrix_reset(&m);
    Matrix_free(m);
    printf("Should be null: %x\n", m);
    Matrix_reset(&m);

}

void t_matclone() {

    ejovo_seed();

    Matrix *m = Matrix_rand(5, 5);
    Matrix *m_clone = matclone(m);

    Matrix_reset(&m);
    Matrix_free(m_clone);


}

void t_matcatch() {

    ejovo_seed();

    Matrix *m = Matrix_rand(10, 10);
    Matrix *m1 = NULL;
    Matrix_catch(&m1, matclone(m));
    Matrix_catch(&m1, Matrix_add(m, m1));

    Matrix_free(m);
    Matrix_free(m1);

}

void t_vector_linspace() {

    Vector *v = Vector_linspace(1, 0, 4);
    assert(Vector_first(v) == 1);

    Matrix_print(v);

    assert(Vector_last(v) == 0);

    Matrix_reset(&v);


}