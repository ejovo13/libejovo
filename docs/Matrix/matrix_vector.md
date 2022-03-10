# Vector

This submodule introduces the type alias `Vector`, which is really just a `Matrix` type.

```
typedef Matrix Vector;
```

This might seem superfluous but it allows the code to be more expressive. When we use the `Vector` type alias, we communicate to the caller of the function that we are going to interpret the the elements stored in a `Matrix`'s `data` pointer as a one-dimensional vector. Thus, we use `Vector` to signal that we are working with a row or column vector. Any `Matrix` can be passed into a function that accepts a `Vector` but be aware that shape information will be lost when outputting a new `Vector`.

The header file `matrix_vector.h` contains a comprehensive API for treating `Matrix` objects as one-dimensional entities. The `Vector` "class" gives us a powerful framework that will be used as the basis of almost all the other scientific routines. `Vectors` are used to generate randiom variates, create equally spaced intervals, encode polynomials, compute the value of functions, perform numeric quadrature, etc. etc.

### Instantiation

The `Vector` counterpart of `Matrix_new` is `Vector_new`, which returns a column vector by default:

```
Vector *v = Vector_new(10); // identical to Matrix_new(10, 1);
```

If we want a row vector as the output, call the utility function `asrow`.

```
Vector *v = asrow(Vector_new(10)); // identical to Matrix_new(1, 10);
```

`asrow` also comes packaged with its dual, `ascol`. Keep in mind that `asrow`/`ascol` do not return a newly allocated
array as a functional style pattern would suggest. They specifically modify the `Vector`'s fields **in-place** to switch the `nrows` and `ncols`. Since the memeory of `Matrix` is already in a contiguous block, swapping the fields has the simple effect of changing how the same data is interpreted.

```
Vector *v = ascol(asrow(Vector_new(100))); // identical to Vector_new(100);
```

### Destruction

Destroy a vector with `Vector_free` or `Vector_reset` which are really just wrapper functions for their `Matrix` counterpart. Here is where we could argue that the API is redundant. I agree. In my personal code I call `Matrix_free` and `Matrix_reset` but I wanted to provide these two functions for completeness.

```
Vector_reset(&v);
```

Or

```
Vector_free(v);
```

With `Vector_reset` being preferred as it nullifies the pointer.

### Useful Constructors

##### Create a new vector from thin-air

Following some of R's conventions, we provide a few basic routines to generate random variables that follow the usual probability distributions

```
Vector *X = Vector_rnorm(100, 0, 1) // X ~ N(0, 1), 100 observations
Vector *Y = Vector_runif(50, 0, 1)  // Y ~ U(0, 1),  50 observations
Vector *Z = Vector_rexp(100, 5)     // Z ~ EXP(rate= 5), 100 observations
```

The default random number generator can be seeded with random noise from the OS at the time of execution by calling `ejovo_seed()` somewhere in your program or by calling `ejovo_set_seed(seed)`, where `seed` is an integer.

We can create other `Vectors` of discrete integers sampled from a discrete Uniform distribution between `0` and `10` with `Vector_rand`. Just like `Matrix_rand` and `Matrix_random`, we can generate a discrete Uniform distribution between `a` and `b` with
`Vector_random(n, a, b)`. These functions return a new column vector by default.

```
Vector *rand = Vector_rand(10);
Vector *rando = Vector_random(10, 4, 20);
```

Used ubiquitously in scientific applications are the beloved  `linspace` and `range` functions. A `Vector`-based API for these functions are as follows:

```
Vector *v_lin = Vector_linspace(1, 2, 100); // Create a vector of length 100 equally spaced between 1 and 2.
Vector *v_ran = Vector_range(1, 100, 2); // Create a vector between 1 and 100 whose starting element is 1 and whose step size is 2
```

##### New vector from existing data

A `Vector` can be constructed from an already existing vector with the `Vector_clone` function, which really just calls `Matrix_clone` under the surface:

```
Vector *rand_clone = Vector_clone(rand);
```

or from an existing matrix

```
// suppose that m already exists and is of type Matrix *
Vector *m_col_clone = Matrix_as_col(m);
Vector *m_row_clone = Matrix_as_row(m);

Vector *m_vec = Vector_from_matrix(m); // Creates a new column vector from an existing matrix
```

or from an existing vector

```
Vector *v_col_from_vec = Vector_as_col(v);
Vector *v_row_from_vec = Vector_as_row(v);
```

or from an existing C built-in array:
```
Vector *vd = Vector_from((double []) {1.0, 2.0, 3.0, 4.0, 5.0}, 5);
```

or using the variadic function `vector` that is similar to R's `c` function:

```
Vector *my_vec = vector(5, 1.0, 2.0, 3.0, 4.0, 5.0);
```

lastly, we can create a new `Vector` from a `begin` and `end` `MatIter`:

```
Vector *v_iter = Vector_from_iter(Matrix_begin(m), Matrix_end(m));
```


If you've worked with iterators in C++, the idea is similar. Basically, A `MatIter` allows us to abstract away the petty matrix concepts of "rows" and "columns", replacing them with an iterator object that will visit specific memory addresses to encapsulate a high level behavior. `MatIter`s also provide a unified interface to deal with the elements of a `Matrix` and a `Vector` in a similar fashion.

Please consider checking out the [MatIter section](matrix_iter.md) for a comprehensive introduction to the role that `MatIter`s play in libejovo.

**Attention**:

- The first parameter to `vector` must be an `int` indicating the number of `double`s that follow as parameters. The rest of the parameters _must_ be in their `double` literal form. The function call `vector(2, 1, 2);` is *undefined*.
- `Matrix_as_col`, `Matrix_as_row`, `Vector_as_col`, `Vector_as_row` all return a newly allocated `Vector` where as `asrow` and `ascol` modify a `Vector` in place.


### Inquiry Functions

This section contains a demonstration of functions that get information about the state of a `Vector`.

`Vector_size` returns the number of elements in a `Vector`
```
Vector *v = Vector_new(100);
size_t s = Vector_size(v); // returns 100
```

`Vector_set`, `Vector_set_first`, and `Vector_set_last` are used to set the elements of a `Vector`.

```
Vector_set(v, 4, 10);      // Sets the 5th element of v to 10.0

Vector_set_first(v, 99.0); // Sets the first element of v to 99.0
Vector_set_last(v, 1.0);  // Sets the last element of v to  1.0
```

These `Vector_` functions are **always** verifying that the bounds are valid. When writing performant code, consider using the lower level routines `vecset` that doesn't check any boundaries and instead directly accesses the `Vector`'s memory. Check out the **safe** vs **unsafe** section here.
**-------------ADD A LINK HERE----------------**

To retrieve the double values at a certain position, use the `Vector_at`, `Vector_first`, and `Vector_last` functions:

```
Vector_at(v, 4); // Returns 10.0
Vector_last(v); // Returns 99.0
Vector_first(v); // Returns 1.0
```

To create `MatIter` associated with a vector, use the `_begin`, `_end`, and `_iter` functions:

```
MatIter third = Vector_iter(v, 2);
MatIter start = Vector_begin(v);
MatIter end   = Vector_end(v);
```

As a reminder, `MatIter` can be used to systematically visit the elements of a `Matrix`. Consider an alternative for loop as follows;

```
Vector *vrand = Vector_rnorm(100, 0, 1);

const MatIter end = Vector_end(v);

for (MatIter it = Vector_begin(v); !MatIter_cmp(it, end); it = MatIter_next(it)) {
    printf("Visiting value: %lf\n", MatIter_value(it));
}

```

If you would like a raw pointer to the `nth` element of a `Vector`, use the `Vector_access` function:
```
double *raw_ptr = Vector_access(v, i);
```

### Operations

##### Dot Product

To take the dot product of two `Vectors`, call `Vector_inner` or `Vector_dot`. These two functions are identical.

```
Vector *v = Vector_rnorm(100, 0, 1);
Vector *u = Vector_rnorm(100, 5, 5);

printf("<u, v> = %lf\n", Vector_dot(u, v)); // Vector_inner(u, v) works here as well
```

##### Norms

The euclidean norm of a `Vector` can be accessed with `Vector_norm`. Other _p-norms_ can be computed with `Vector_pnorm`. For the special cases of the p-norm `p = 1` we can use `Vector_sum` and for `p = \infty` we can use `Vector_max`.

```
double euc_norm = Vector_norm(v);
double pnorm_sum = Vector_sum(v);
double pnorm_max = Vector_max(v);
```

We can get a newly allocated unit vector (according to the euclidean norm) with `Vector_normalize`. If we want to normalize the vector in-place, that is to modify the contents of the passed vector and not return a newly allocated one, use `vecnormalize`.

```
Vector v_normalized = Vector_normalize(v);

vecnormalize(v_normalized); // "normalize" an already normalized vector
```

##### Projection

Take the projection of `u` onto `v` with `Vector_project_onto(u, v)`.

```
Vector *u = vector(3, 6.0, 2.0, 3.0);
Vector *v = vector(3, 1.0, 0.0, 0.0);

Vector *proju_v = Vector_project_onto(u, v); // proju_v = {6.0, 0.0, 0.0}
```

Finally, apply a `function` - a C function whose type signature is (in Haskell notation) `double -> double` - to all of
the elements of a `Vector` with `Vector_map(v, fn)`:

```
Vector *x = Vector_linspace(-5, 5, 1000);
Vector *y = Vector_map(x, sin); // Map sin to all of elements of x.
```

If you want to pass in your own custom function, you have to manually declare your function first. Unfortunately, C doesn't support lambda expressions and closures so we can get around this with by declaring our own function somewhere in-scope.

```
double custom_fn(double x) {

    double out = 0;

    // do thing with out

    return out;
}
```

and then passing the function pointer as the second parameter to `Vector_map(x, fn)`.

```
Vector *x = Vector_linspace(1, 20, 50);
Vector *y = Vector_map(x, custom_fn);
```
