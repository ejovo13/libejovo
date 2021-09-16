#include <stdio.h>

// Suite recurrente d'ordre 2

#define A 5
#define B 10

int suite_n(int n) {
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

    printf("Please enter a positive integer n\n\n");

    int n = 0;

    scanf("%d", &n);

    printf("The %dth value in the series is: %d\n", n, suite_n(n));


    return 0;
}