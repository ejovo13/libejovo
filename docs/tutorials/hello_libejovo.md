# Hello libejovo

**Goal:** Compile your first program using libejovo

**Tutorial level:** Beginner

**Time:** 5 minutes

**Contents:**

- [Background](#Background)

## Background

libejovo is a set of routines that allow for pleasant numerical computing inside of C programs without having to go somewhere else and use a software package like MATLAB or R.

## Prerequisites

Before starting these tutorials, make sure you've installed libejovo by following the instructions [here](../Installation.md)

## Tasks

### 1. Create a new C program
Create a new file called `hello_ejovo.c` and define a main function:

```
#include <stdio.h>

int main(int argc, char **argv) {

    return 0;
}
```

### 2. Include libejovo's headers

Include the declarations of all libejovo's functions by including the `ejovo.h` header:

```
#include <stdio.h>
#include "ejovo.h"

int main(int argc, char **argv) {

    return 0;
}
```

### 3. Call a libejovo function

We will test out the library by creating a new 10 x 5 matrix of doubles (`Matrix_d`) and then printing it to the screen.

```
#include <stdio.h>
#include "ejovo.h"

int main(int argc, char **argv) {

    Matrix_d *A = Matrix_new_d(10, 5); // create a new matrix
    Matrix_print_d(A);               // print to the screen
    Matrix_free_d(A);                // free the memory managed by A

    return 0;
}
```


Without explaining to much, the `_d` that is appended to all of the function calls indicates that we are operating on a Matrix whose elements are doubles.

Libejovo comes equipped with built-in support for complex (`_c`), integer (`_i`), and float (`_f`) types. For more information, see the [Matrix](../Matrix/matrix.md) entry of the [Concepts](../Concepts.md) section.

### 4. Compile and run the program

Now we are ready to actually compile our hello world program. Libejovo depends on the C std's math library which we unfortunately have to manually link.

If libejovo was installed to a path that is on your compiler's default search path, compiling this program is as easy as:
```
gcc hello_ejovo.c -o hello -lm -lejovo 
```

If you configured your own `CMAKE_INSTALL_PREFIX` during installation, make sure to indicate where to search for header files with the `-I` flag and library search paths with `-L`:

```
gcc hello_ejovo.c -o hello -lm -lejovo -I<your_install_path> -L<your_install_path>
```