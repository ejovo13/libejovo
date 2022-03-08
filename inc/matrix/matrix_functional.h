#pragma once

#include "matrix.h"
#include "matrix_core.h"
#include "matrix_vector.h"

Vector *filter(const Vector *__v, predicate_fn __pred);