#ifndef MATRIX_D_H
#define MATRIX_D_H

// Matrix of doubles

#undef MATRIX_TYPE
#undef TYPE_SUFFIX

#undef MATRIX_FLOAT
#undef MATRIX_INT
#undef MATRIX_COMPLEX

#define MATRIX_DOUBLE
#define MATRIX_TYPE double
#define TYPE_SUFFIX _d 

#include "ejovo_matrix.h"

#endif // MATRIX_D_H