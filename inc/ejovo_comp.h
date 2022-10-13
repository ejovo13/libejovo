#pragma once
#define _USE_MATH_DEFINES
// simple complex framework
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define COMPLEX_TYPE double

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct complex_t {

    COMPLEX_TYPE re;
    COMPLEX_TYPE im;

} Complex;

typedef Complex (*Fnz) (Complex);
typedef double (*Fnx) (double);


/**
 * Calculate e^(ix)
 */
Complex Complex_exp(COMPLEX_TYPE __x);




// I'm just going to try this shit and see if it works??



// I will eventually want a function type to take in the fourier transform.

// Am I working with pointers like I always do?
/**
 * Create a new Complex number and return a pointer
 */
Complex *Complex_new(COMPLEX_TYPE __re, COMPLEX_TYPE __im);

// e^i(__x)
Complex Complex_exp(COMPLEX_TYPE __x);

// ae^i(__th)
Complex Complex_aexp(COMPLEX_TYPE __a, COMPLEX_TYPE __th);

/**
 * Add two complex numbers, creating a third
 *
 */
Complex Complex_add(const Complex __z1, const Complex __z2);

Complex Complex_mult(const Complex __z1, const Complex __z2);

Complex Complex_div(const Complex __z1, const Complex __z2);

void Complex_print_polar(const Complex __z);

// __z1 - __z2
Complex Complex_sub(const Complex __z1, const Complex __z2);

Complex Complex_conj(const Complex __z);

void Complex_print(const Complex __z);

// Modulus of complex number
COMPLEX_TYPE Complex_mod(const Complex __z);

// principal argument calculated with atan2 (-pi, pi]
COMPLEX_TYPE Complex_arg(const Complex __z);


Complex *Complex_new_polar(COMPLEX_TYPE __mod, COMPLEX_TYPE __arg);


Complex Complex_multr(const Complex __z, const double __scalar);

// Some constant values that are important
Complex Complex_one(void);

Complex Complex_i(void);

Complex Complex_zero(void);

// return unitary minus of a complex value
Complex Complex_min(const Complex __z);


