#ifndef MATRIX_F_H
#define MATRIX_F_H

// Matrix of doubles

#undef MATRIX_TYPE
#undef TYPE_SUFFIX

#undef MATRIX_INT 
#undef MATRIX_DOUBLE
#undef MATRIX_COMPLEX

#define MATRIX_FLOAT
#define MATRIX_TYPE float 
#define TYPE_SUFFIX _f 

// #ifndef MATRIX_FLOAT_DEFINED
// #define MATRIX_FLOAT_DEFINED

//     typedef struct Matrix_f {
//         float *data;
//         size_t nrows;
//         size_t ncols;
//     } Matrix_f;

// #endif

#include "ejovo_matrix.h"

#endif // MATRIX_F_H