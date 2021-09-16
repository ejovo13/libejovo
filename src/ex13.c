// Nombres Premiers

#include <stdio.h>
// #include <stdlib.h>
#include <math.h>
#include <stdbool.h>


// int get_rand_int(int max) {
// // get random integer between 1 and max
//     double x = ((double) rand()) / RAND_MAX;
//     return (int) ceil(x * max);
// }

#define MAX 100

bool is_prime(int p) {

    if( p == 0 || p == 1) {
        return true;
    }

    int p_root = ceil(sqrt(p));

    for (int i = 2; i <= p_root; i ++) {

        if ( p % i == 0 ) {
            return false;
        }
    }

    return true;
}

int main() {

    int m = 0;

    printf("Please input a positive integer\n\n");

    scanf("%d", &m);

    for (int i = 2; i <= m; i++) {

        if ( is_prime(i) ) {
            printf("%d\n", i);
        } else {
            printf("%d  ", i);
        }
    }

    printf("\n\n");

    return 0;
}