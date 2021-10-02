// ecrire une fonction nbDeChiffres - on est en C, pas C++, pas Java - j'ecris nb_chiffres moi
#include <math.h>
#include "ejovo_print.h"
#include <stdint.h>

int nb_chiffres(int x) {
// Return the number of digits for an integer
// nb_chiffres(-10) returns 2
// nb_chiffres(100) returns 3
    return (int) log10((double) abs(x) ) + 1;
}

char * int_to_string(int x) {
// Take an integer and return a null terminated string of that integer.
// if the number is negative, take that into account and return a string that
// includes the negative sign

    int n_digits = nb_chiffres(x);
    char * num_str;

    if ( x < 0 ) {

        num_str = (char *) malloc(sizeof(char) * n_digits)

    }
}

int extrait_nombre(int x, uint32_t n, uint32_t lg) {





}


int main() {


    return 0;
}