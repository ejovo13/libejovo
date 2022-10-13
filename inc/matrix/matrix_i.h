#ifndef MATRIX_I_H
#define MATRIX_I_H


#undef MATRIX_TYPE
#undef TYPE_SUFFIX

#undef MATRIX_FLOAT
#undef MATRIX_DOUBLE
#undef MATRIX_COMPLEX

#define MATRIX_INT
#define MATRIX_TYPE int
#define TYPE_SUFFIX _i


// #ifndef MATRIX_INT_DEFINED
// #define MATRIX_INT_DEFINED

//     typedef struct Matrix_i {
//         int *data;
//         size_t nrows;
//         size_t ncols;
//     } Matrix_i;

// #endif

#include "ejovo_matrix.h"

#endif // MATRIX_I_H