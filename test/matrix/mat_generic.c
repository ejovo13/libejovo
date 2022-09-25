#include "ejovo_matrix_generic.h"
#include <assert.h>
#include <stdbool.h>

// Try to define two types of matrices

int main() {

    ejovo_seed();

    Matrix_d *m = Matrix_new_d(10, 2);

    Matrix_print_d(m); 
    // MATRIX(int) *mi = Matrix_i_new(10, 10); 

    // Matrix_int_print(mi);

    

    return 0;
}