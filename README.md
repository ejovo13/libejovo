<!-- # Libejovo
[![Coverage Status](https://coveralls.io/repos/github/ejovo13/Informatique-TP/badge.svg?branch=master)](https://coveralls.io/github/ejovo13/Informatique-TP?branch=master) -->

![example workflow](https://github.com/ejovo13/libejovo/actions/workflows/Mac.yml/badge.svg)
![example workflow](https://github.com/ejovo13/libejovo/actions/workflows/Ubuntu.yml/badge.svg)
[![Documentation Status](https://readthedocs.org/projects/libejovo/badge/?version=latest)](https://libejovo.readthedocs.io/en/latest/?badge=latest)

## Introduction
Libejovo is the synthesis of my Applied Mathematics and Computer Science education. Centering around the fundamental type `Matrix`, Libejovo contains a number of general purpose routines that span the following subjects:

- Numeric Linear Algebra
    - Matrix Decompositions
    - Iterative Methods (Ax = b, eigenvalue methods)
    - Direct Methods (Ax = b, eigenvalue methods)
    - Random Matrix generation
    - Basic framework of matrix operations, additions, norms
    - [ ] inquiry functions like is Hermitian, rank, dim, etc..
    - Polynomial interpolation
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

## Documentation

A high-level API hosted at `readthedocs` is available [here](https://libejovo.readthedocs.io/en/latest/). This documentation tells a story about what this library is and snippets of code that demonstrate how to use and think with this library. For a more technical API, consult the `doxygen` documentation hosted with github pages.

## Build
Build out of source with `CMake`
```
git clone git@github.com:ejovo13/libejovo.git

# configure build
cmake -B ./build
cmake --build ./build
```

To test that the functions are working properly, run `CTest` in the `build` directory.
```
cd ./build
ctest
```

We can inspect the symbols of `libejovo.a` with
```
nm ./lib/libejovo.a
```

where `./` is the top-level source directory.
## As a dependency
To include this project as a dependency, there are two **super easy** methods. The first consists of building and installing this project, followed by adding the header file paths to your `$C_INCLUDE_PATH`. When including this library in another `CMake` project, simply link the `ejovo` library with the `target_add_libary` command.

```
cmake --install build
```

Alternatively, we can use gitsubmodules to lock a reference to a commit of this repository in another project. For an example, see [this project](https://github.com/ejovo13/Informatique-TP) that uses `libejovo` as a dependency. I was blown away with how simple it was. All you have to do when cloning is make sure you download the submodule's files and then add the submodule as a subdirectory to your cmake project with `add_subdirectory`. `CMake` will take care of the rest!

# In Progress

I am currently working on getting a proper High-level API established at readthedocs. The skeleton is already in place and provides a brief introduction to this library. The technical documentation is also a work in progress, with about half of all publicly exposed functions being documented.

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
