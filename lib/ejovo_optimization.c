// Routines that deal with the concepts and functions that we deal with our
// optimisation course

// fixed point iteration
// newtons method (univariable and multivariables)
// secants method

#include "math.h"
#include "stdbool.h"

// let's try and implement a basic secant method routine.

typedef double (* function) (double);

// One way to do this is to keep track of two variables, x_n, x_{n - 1}, and x_{n + 1}

// secant's method only requires the function to be defined.

double secantMethod(function __fn, double __x0, double __x1) {

    double m = __fn(__x1) - __fn(__x0) / (__x1 - __x0);
    double x_n1 = 0;
    double fprime = 

    bool should_iterate = true;

    while (should_iterate) {

        x_n1 = x_n


    }




}