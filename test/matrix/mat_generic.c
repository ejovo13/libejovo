#include "ejovo_matrix_generic.h"
#include <assert.h>
#include <stdbool.h>

// Try to define two types of matrices
DECLARE_MATRIX(int);

int main() {

    ejovo_seed();

    Matrix_d *m = Matrix_d_new(10, 2);

    Matrix_d_print(m); 
    // MATRIX(int) *mi = Matrix_i_new(10, 10); 

    // Matrix_int_print(mi);

    

    return 0;
}