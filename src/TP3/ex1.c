// Écrire un algorithme récursif qui affiche l’écriture inverse d’un entier donné en entrée (par
// exemple si on entre -2344, on obtiendra l’affichage -4432).

#include "ejovo_print.h"
#include "math.h"
#include <stdio_ext.h>
#include <stdbool.h>
#include <stdlib.h>


// Creer une fonction recursive pour afficher les entiers a l'inverse
void reverse(long n) {

    if (n < 0) { // Include negative sign if the value is negative
        printf("-");
        n = -n; // Use the absolute value of n for the rest of the digits
    }

    if (n < 10) {
        printf("%ld", n);
    } else {
        printf("%ld", n%10);
        reverse( (n - (n % 10)) / 10 ); // for 123, print 3 then pass 12 to reverse to print 2, then pass 1 and print 1
    }
}


int main() {

    long int user_input = 0;

    printf("Please enter any integer: ");
    scanf("%ld", &user_input);

    printf("Recursive reverse function:\n");
    reverse(user_input);
    printf("\n");

    return 0;
}