// Suite de Fibonacci

#include "hw_printer.h"

long int compute_fib(long int n) {

    if (n == 0 || n == 1) {
        return 1;
    } else {
        return compute_fib(n-1) + compute_fib(n-2);
    }
}

void fib_demo() {

    for (int fib = 0; fib < 10; fib ++) {

        printf("fib(%d) = %ld\n", fib, compute_fib(fib));

    }

}

int main() {

    ex(10, "Computer le nieme nombre de Fibonacci");

    long int n = 0;

    printf("Please enter the nth Fibonacci value that you would like to compute\n");

    scanf("%ld", &n);

    if (n > 40) {
        printf("Please enter a smaller number\n");
        return 2;
    }

    printf("fib(%ld) = %ld\n", n, compute_fib(n));

    return 0;
}
