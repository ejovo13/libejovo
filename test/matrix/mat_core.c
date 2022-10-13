#include "ejovo_matrix_generic.h"
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

    Matrix_d *m = matalloc_d(10, 10);

    assert(m);
    assert(m->data);
    assert(m->ncols == 10);
    assert(m->nrows == 10);
    // Matrices allocated with matalloc should NOT be used.
    // This is because the values are uninitialized


    Matrix_set_d(m, 5, 5, 100);
    // Matrix_print_d(m);
    Matrix_reset_d(&m);
    Matrix_free_d(m);
    printf("Should be null: %p\n", m);
    Matrix_reset_d(&m);

}

void t_mat_clone() {

    ejovo_seed();

    Matrix_d *m = Matrix_rand_d(5, 5);
    Matrix_d *m_clone = matclone_d(m);

    Matrix_reset_d(&m);
    Matrix_free_d(m_clone);


}

void t_mat_catch() {

    ejovo_seed();

    Matrix_d *m = Matrix_rand_d(10, 10);
    Matrix_d *m1 = NULL;
    Matrix_catch_d(&m1, matclone_d(m));
    Matrix_catch_d(&m1, Matrix_add_d(m, m1));

    Matrix_free_d(m);
    Matrix_free_d(m1);

}

void t_vector_linspace() {

    Vector_d*v = Vector_linspace_d(1, 0, 4);
    assert(Vector_first_d(v) == 1);

    Matrix_print_d(v);

    assert(Vector_last_d(v) == 0);

    Matrix_reset_d(&v);


}