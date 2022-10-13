// simple complex framework
#include "ejovo_comp.h"
// #include <math.h"

// I will eventually want a function type to take in the fourier transform.

// Am I working with pointers like I always do?
/**
 * Create a new Complex number and return a pointer
 */
Complex *Complex_new(COMPLEX_TYPE __re, COMPLEX_TYPE __im) {

    Complex *z = (Complex *) malloc(sizeof(Complex));
    z->re = __re;
    z->im = __im;
    return z;

}

Complex *Complex_new_polar(COMPLEX_TYPE __mod, COMPLEX_TYPE __arg) {

    return Complex_new(__mod * cos(__arg), __mod * sin(__arg));

}


Complex Complex_multr(const Complex __z, const double __scalar) {

    Complex z = {__z.re * __scalar, __z.im * __scalar};
    return z;

}

// e^i(__th)
Complex Complex_exp(COMPLEX_TYPE __th) {

    Complex z = {cos(__th), sin(__th)};
    return z;

}
// ae^i(__th)
Complex Complex_aexp(COMPLEX_TYPE __a, COMPLEX_TYPE __th) {
    Complex z = {__a * cos(__th), __a * sin(__th)};
    return z;
}

/**
 * Add two complex numbers, creating a third
 *
 */
Complex Complex_add(const Complex __z1, const Complex __z2) {

    Complex z = {__z1.re + __z2.re, __z1.im + __z2.im};
    return z;

}

Complex Complex_mult(const Complex __z1, const Complex __z2) {

    Complex z = {__z1.re * __z2.re - (__z1.im * __z2.im), __z1.re * __z2.im + __z1.im * __z2.re};
    return z;

}

// Complex Complex_div(const Complex __z1, const Complex __z2) {
//     // Complex z =
// }

// __z1 - __z2
Complex Complex_sub(const Complex __z1, const Complex __z2) {

    Complex z = {__z1.re - __z2.re, __z1.im + __z2.im};
    return z;

}

Complex Complex_conj(const Complex __z) {

    Complex z = {__z.re, -__z.im};
    return z;

}

void Complex_print(const Complex __z) {

    printf("%lf + %lfi\n", __z.re, __z.im);

}

void Complex_print_polar(const Complex __z) {

    printf("%lfe^{%lfi}\n", Complex_mod(__z), Complex_arg(__z));

}

COMPLEX_TYPE Complex_mod(const Complex __z) {
    return sqrt((__z.re * __z.re + __z.im * __z.im));
}

COMPLEX_TYPE Complex_arg(const Complex __z) {
    return atan2(__z.im, __z.re);
}

// Some constant values that are important
Complex Complex_one(void) {
    Complex z = {1, 0};
    return z;
}

Complex Complex_i(void) {
    Complex z = {0, 1};
    return z;
}

Complex Complex_zero(void) {
    Complex z = {0, 0};
    return z;
}

// return unary minus of a complex value
Complex Complex_min(const Complex __z) {

    Complex z = {-__z.re, -__z.im};
    return z;

}

// Compute the discrete fourier transform at a single frequency
// Complex DFTz_point(Fnz __fn, Complex __x ) {

// }


