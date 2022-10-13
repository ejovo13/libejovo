// complex matrix version

#ifndef MATRIX_C_H
#define MATRIX_C_H

// Matrix of doubles

#undef MATRIX_TYPE
#undef TYPE_SUFFIX

#undef MATRIX_FLOAT
#undef MATRIX_INT
#undef MATRIX_DOUBLE


#define MATRIX_COMPLEX
#define MATRIX_TYPE double complex
#define TYPE_SUFFIX _c

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