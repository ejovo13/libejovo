# Matrix Module

###### Introduction

The matrix module of the ejovo library consists of the fundamental data type `Matrix` - a fixed container of `double`s - and a large assortment of supporting functions that are used to accomplish various tasks in Scientific Programming.

Whereas the compiled functions end up in the library `ejovo`, we can include the interface for the matrix module by including the header `ejovo_matrix.h` and linking to `libejovo.a` at compile time. When using this project as a git submodule dependency, this is as simple as including the top-level CMake project directory as a subdirectory for the main project.

###### Organization

The Matrix module is internally divided into a set of submodules that attempt to modularize different common behaviors and to clean up the development structure for `ejovo`.

The Matrix module, whose interface is defined in `ejovo_matrix.h`, contains the following submodules (whose interface is declared in `matrix/matrix_xxx.h`):

- `matrix_compute.c`
- `matrix_core.c`
- `matrix_dist.c`
- `matrix_foreach.c`
- `matrix_getset.c`
- `matrix_iter.c`
- `matrix_linear.c`
- `matrix_special.c`
- `matrix_state.c`
- `matrix_stats.c`
- `matrix_vector.c`

Each of these submodules is detailed in this document. A brief introduction to instantiation of the `Matrix` structure is provided by [libejovo](../index.md) and will be elaborated upon in the `MATRIX_FN(core)` section.

## MATRIX_FN(compute)

This submodule contains the routines and ideas explored in Gilbert Strang's Computational Science and Engineering course. Examples include basic techniques for solving PDE boundary value problems and an introduction to scientific computing. The symmetric matrices `K`, `C`, `T`, and `B`, which represent various configurations of Finite Difference methods and are presented in the opening chapters of his book, can be accessed with the `MATRIX_FN(K)(n)`, `MATRIX_FN(C)(n)`, `MATRIX_FN(T)(n)`, and `MATRIX_FN(B)(n)` routines.

At the time of writing this document, the `MATRIX_FN(compute)` submodule is quite empty but as I make progress through the course I will update the package.

## MATRIX_FN(core)

The fundamental heart of the Matrix module, `MATRIX_FN(core)`, provides - unsurprisingly - the core features of the `Matrix` data structure. This includes the process of memory allocation, interpretation of indices, routines to print a `Matrix` to the console, etc.

###### API Philosophy

As described in the landing page, the `Matrix` API adopts an OOP strategy where the object (`Matrix`) is performing an action (e.g, `print`). This behavior is encapsulated in the `MATRIX_FN(print)` function, which takes a const pointer to a `Matrix` and prints its contents to the terminal. There are a number of other routines however that are spelled in all lowercase, without any underscores for easy parsing of the function name. This subroutines are utility functions that perform no higher-level parameter validation and just plainly perform an action. For example, the function `matalloc` performs no sanity checks on its inputs and goes ahead and allocates the proper space for a `Matrix`. The function `MATRIX_FN(new)`, on the other hand, verifies that the inputs are valid and then procedes to call the lower level `matalloc`. *Unless you know what you are doing, prefer to call the `MATRIX_FN()` style functions to validate the input to functions*.

#### Matrix constructors

Some of this content will be a repeat of what's already been showcased in [libejovo](../index.md).

###### Allocating new memory

Construct a `Matrix` whose elements are all `0` with `MATRIX_FN(new)(m, n)`, where `m` is the number of rows and `n` is the number of columns:

```
Matrix *m = MATRIX_FN(new)(10, 3);
```

###### Copy constructors
Some constructors consist of generating completely new elements while others consist of creating a new `Matrix` from either another `Matrix` object or by an already existing one-dimensional base array.

The first important function is `MATRIX_FN(clone)` which clones the contents of the first `Matrix` and returns a brand-spanking new `Matrix` object who "owns" its memory. The signature of `matlone` is: `Matrix *MATRIX_FN(clone)(const Matrix *m)` and thus does not modify the original `Matrix` passed in as argument, it only duplicates it.

```
Matrix *m_dup = MATRIX_FN(clone)(m);
```

If we don't want to Create a deep copy to the underlying data but we want to interpret the data differently, say to eventually interpret the 64 memory block of doubles as a 4 x 16 matrix rather than 8 x 8, we can perform a shallow copy that instantiates a new `Matrix` object whose `data` field points to the same, already allocated, block of memory.

```
Matrix *m_shallow = MATRIX_FN(shallow_copy)(m);
```

In this example, `m_shallow->data == m->data` but `m_shallow != m`. We can instantiate a `Matrix` object if we pass in a constant array. The default behavior of the newly constructed `Matrix` is to copy the contents of the passed array (i.e. _take ownership_ of the data).

```
Matrix *m_array = MATRIX_FN(from)((double []) {1, 2, 3, 4, 5, 6, 7, 8}, 4, 2);
```

This will create a new `4 x 2` `Matrix` whose elements are filled in `ROW_MAJOR` order. This row major choice was made to align with C's default row indexing scheme.

#### Accessing Elements

Different ways of acessing elements will be covered in-depth in the `MATRIX_FN(getset)` submodule. In the meantime, consider the two elementary methods of accessing elements:

```
double ij = MATRIX_FN(at)(m_array, 1, 2); // 4.0
MATRIX_FN(set)(m_array, 1, 2, 13);        // Set m_array[1, 2] = 13
```

It is important to note that unlike other languages such as Fortran and MATLAB, this library has adopted 0-based indexing.