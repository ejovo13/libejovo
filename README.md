<!-- # Libejovo
[![Coverage Status](https://coveralls.io/repos/github/ejovo13/Informatique-TP/badge.svg?branch=master)](https://coveralls.io/github/ejovo13/Informatique-TP?branch=master) -->

![example workflow](https://github.com/ejovo13/libejovo/actions/workflows/Mac.yml/badge.svg)
![example workflow](https://github.com/ejovo13/libejovo/actions/workflows/Ubuntu.yml/badge.svg)

## Introduction
Libejovo is the synthesis of my Applied Mathematics and Computer Science education. Centering around the fundamental type `Matrix`, Libejovo contains a number of general purpose routines that span the following subjects:

- Numeric Linear Algebra
    - Matrix Decompositions
    - Iterative Methods (Ax = b, eigenvalue methods)
    - Direct Methods (Ax = b, eigenvalue methods)
    - Random Matrix generation
    - Basic framework of matrix operations, additions, norms
    - [ ] inquiry functions like is Hermitian, rank, dim, etc..
- Statistics
    - Standard routines (std, mean, var, cor)
    - Functional patterns to operate on columns
    - `DataFrame` structure to write data as csv
- Differential Equations
    - [ ] Basic solvers like euler's method
- Numerical Quadrature
    - [ ] Also not implemented in this C library
    - [ ] Adaptive methods
- Probability
    - Non-naive psuedo random number generators
    - Inverse transform, rejection, box-muller methods for sampling from probability distributions
    - [ ] Matrices sampled from the Gaussian Orthogonal Ensemble



# TODO

## Matrices

- [ ] Finish technical documentation with doxygen
- [ ] Add general API documentation with readthedocs
- [ ] Add complete documentation to `ejovo_matrix.h`
- [ ] Provide more conversion functions between a Matrix and a normal c array
- [ ] Finish Complete testing suite of Matrix.

## Rand
- [ ] Please for the love of god add floating-point functions

# Future

I might want to add a bitflag to each matrix to be able to keep track of whether or nor it is a transpose, if it's hermitian, symmetric, etc. etc.

## Long term project goals

I want to make a really nice finished product that has the majority of fundamental linear algebra routines:

SVD, QR, LU, Cholesky, Eigenvalue decomposition, Gaussian Elimination.

I'd like to eventually (Throughout the next quarter) implement more of the iterative algorithms used to solve large systems of equations and eigenproblems

### API

I'd like to be able to switch from Column-major and Row-major indexing seamlessly.
The hookup is that I would have to change how rows and cols are copied, although this would require an adjustment to just a few very low-level functions.
