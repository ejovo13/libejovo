// Suite de Fibonacci

#include <stdio.h>

int compute_fib(int n) {

    if (n == 0 || n == 1) {
        return 1;
    } else {
        return compute_fib(n-1) + compute_fib(n-2);
    }
}

void fib_demo() {

    for (int fib = 0; fib < 10; fib ++) {

        printf("fib(%d) = %d\n", fib, compute_fib(fib));

    }

}

int main() {

    int n = 0;

    printf("Please enter the nth Fibonacci value that you would like to compute\n");

    scanf("%d", &n);

    printf("fib(%d) = %d\n", n, compute_fib(n));

    return 0;
}
