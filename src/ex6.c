#include "hw_printer.h"
#include <stdbool.h>

int PGCD(int a, int b) {
// Euclid's algorithm to find the greates common divisor

    int r = 0;

    do {
        // take the remainder of [bigger number] divided by [smaller number]
        if (a > b) {
            a = a % b;
            // r = a;
        } else {
            b = b % a;
            // r = b;
        }
    } while(a != 0 && b != 0);

    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main() {

    // Lit deux entiers, verifie qu'ils sont bien strictement positifs et affiche leur PGCD

    ex(6, "Calculer le PGCD de deux entiers");

    printf("Please enter two integers (a, b) to compute the GCD(a, b)\n\n");

    int a = 0, b = 0;

    scanf("%d", &a);
    scanf("%d", &b);

    if ( a <= 0 || b <= 0) {
        printf("Both a and b must be strictly positive, exiting with return code 1\n");
        return 1;
    }

    printf("PGCD(%d, %d) = %d\n", a, b, PGCD(a, b));

    return 0;
}
