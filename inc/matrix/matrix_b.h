// byte matrix version

#ifndef MATRIX_B_H
#define MATRIX_B_H

// Matrix of doubles

#undef MATRIX_TYPE
#undef TYPE_SUFFIX

#undef MATRIX_FLOAT
#undef MATRIX_INT
#undef MATRIX_DOUBLE
#undef MATRIX_COMPLEX


#define MATRIX_BYTE
#define MATRIX_TYPE uint8_t
#define TYPE_SUFFIX _b

// #ifndef MATRIX_CMOPLEX_DEFINED
// #define MATRIX_COMPLEX_DEFINED

//     typedef struct Matrix_c {
//         double complex *data;
//         size_t nrows;
//         size_t ncols;
//     } Matrix_c;

// #endif

#include "ejovo_matrix.h"

#endif // MATRIX_D_H