// ecrire une fonction nbDeChiffres - on est en C, pas C++, pas Java - j'ecris nb_chiffres moi
#include <math.h>
#include "ejovo_print.h"
#include "ejovo_rand.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int nb_chiffres(long x) {
// Return the number of digits for an integer
// nb_chiffres(-10) returns 2
// nb_chiffres(100) returns 3
    return (int) log10((double) labs(x) ) + 1;
}

char * int_to_string(int x) {
// Take an integer and return a null terminated string of that integer.
// if the number is negative, take that into account and return a string that
// includes the negative sign

    int n_digits = nb_chiffres(x);
    int str_length = 0;
    char * num_str = NULL;

    if ( x > 0 ) {

        str_length = n_digits + 1;

    } else {

        str_length = n_digits + 2; // Allocate space for the digits, a negative sign, and a null-terminated string

    }

    num_str = (char *) malloc(sizeof(char) * (str_length));
    // printf("Allocated %d digits\n", str_length);
    num_str[str_length - 1] = '\0';

    // printf("Recorded %d digits\n", n_digits);

    sprintf(num_str, "%d", x);
    // printf("Number saved as: %s\n", num_str);


    return num_str;

}

// char * make_format_string(uint32_t num_digits, uint32_t value) {

//     // make character string to pad left with 0's for any integer
//     char * fmt = calloc(6, sizeof(char));
//     fmt[0] = '%';
//     fmt[1] = '0';
//     sprintf(fmt + 2, "%02u", value);
//     fmt[4] = 'd';
//     fmt[5] = '\0';

//     printf("Made format string:\n %s|\n", fmt);


// }

int extrait_nombre(uint32_t x, int n, int lg) {
    // Integer has to be positive

    // want to work with the string version of my integer

    char * x_str = int_to_string(x);
    int num_digits = nb_chiffres(x);
    int result = 0;
    char sub_str[lg + 1];
    sub_str[lg] = '\0';


    // printf("n - lg = %d", n - lg);

    if ( n < lg  || lg > num_digits || n > num_digits) {
        return -1;
    } else {
        // we now want a string starting at the nth element, whose length is lg
        // the full string has length num_digits + 1, where x_str[num_digits - 1] = '\0'

        for(int i = 0; i < lg; i ++) {

            sub_str[i] = x_str[n - lg + i];

        }
    }

    sscanf(sub_str, "%d", &result);

    // printf("Extracted value: %s\n", sub_str);

    return result;
}

bool est_pair(long x) {
    return nb_chiffres(x) % 2 == 0;
}

int somme_des_chiffres(uint32_t x) {

    char * x_str = int_to_string(x);
    int num_digits = nb_chiffres(x);
    int sum = 0;
    int this_digit = 0;

    // printf("What's goot we in this bitch\n");

    for (int i = 0; i < num_digits; i ++) {

        sscanf(x_str + i, "%1d", &this_digit);
        // printf("This digit: %d\n", this_digit);
        sum += this_digit;

    }

    return sum;
}

bool est_couicable(uint32_t x) {

    int num_digits = nb_chiffres(x);
    // bool even_digits = est_pair(x);
    int left_half = 0;
    int right_half = 0;

    // This exercise implicitly wants us to use est_pair, but integer division will take care of the indexing for us if the numb_digits is odd
    left_half = extrait_nombre(x, num_digits/2, num_digits/2);
    right_half = extrait_nombre(x, num_digits, num_digits/2);

    printf("Left half: %d\t", left_half);
    printf("Right half: %d\t", right_half);

    return somme_des_chiffres(left_half) == somme_des_chiffres(right_half);
}


int main() {

    ejovo_seed();
    int i = unif(0, 5000);

    // char * i_str = int_to_string(i);
    // if(! i_str) {
    //     printf("Null string, exiting with error code 1\n");
    //     return 1;
    // }

    // printf("My number as string: %s\n", i_str);

    printf("extraitNombre(%d, 5, 3) = %02d\n", i, extrait_nombre(i, 5, 3));
    printf("somme_des_chiffres(%d) = %d\n", i, somme_des_chiffres(i));
    printf("est_coucable(%d) = %d", i, est_couicable(i));

    // make_format_string(3, 16);


    return 0;
}