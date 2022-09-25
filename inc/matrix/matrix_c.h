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

#include "ejovo_matrix.h"

#endif // MATRIX_D_H