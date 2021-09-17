#include "hw_printer.h"

// Suite recurrente d'ordre 2

#define A 5
#define B 10

long int suite_n(long int n) {
// Return the nth element of the sequence definded by U_n = a*U_{n-1} + b*U_{n-2}

    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return 2;
    } else {
        return A * suite_n(n - 1) + B * suite_n(n - 2);
    }
}

int main() {

    ex(14, "Suite recurrente d'order 2: U_n = a*U_{n-1} + b*U_{n-2}");

    printf("Please enter a positive integer <= 23\n\n\n");

    long int n = 0;

    scanf("%ld", &n);

    printf("The %ldth value in the series is: %ld\n", n, suite_n(n));


    return 0;
}