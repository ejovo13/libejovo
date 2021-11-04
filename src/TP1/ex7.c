// Entier inverse

// Ecrire un program qui demande a l'utilisateur de saisir un entier strictement positif, puis affiche
// cet entier dans le sens inverse. Par example, si l'utilisateur saisit 5628, le programme affiche 8265.

#include "hw_printer.h"
#include <math.h>
#include <stdlib.h>

int main() {

    // get input

    ex(7, "Saisir un entier et afficher son inverse");

    printf("Please enter a strictly positive integer\n\n");

    int n = 0;

    scanf("%d", &n);

    if (n <= 0) {
        return 1;
    }

    // find out the number of digits

    const int num_digits = log10((double) n) + 1;

    char *n_str = (char *) malloc(sizeof(char) * (num_digits + 1));
    char *n_rev = (char *) malloc(sizeof(char) * (num_digits - 1));

    n_str[num_digits] = '\0';
    n_rev[num_digits] = '\0';

    sprintf(n_str, "%d", n);

    for(int i = 0; i < num_digits; i++) {
        n_rev[i] = n_str[num_digits - i - 1];
        // printf("Writing character: %c    ", n_str[num_digits - i - 1]);
        // printf("n_rev[%d] = %c\n", i, n_rev[i]);
    }

    printf("%s has %d digits\n", n_str, num_digits);
    printf("%s reversed is %s\n", n_str, n_rev);


    return 0;
}