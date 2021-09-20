// generer un tablue d'entiers T de taille N dans l'ordre croissant
// premier element est un entier aleatoire compris entre 1 et 10.
// T[i] = T[i-1] + r, avec r un entier aleatoire compris entre 0 et P

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 50
#define P 3

int get_rand_int(int max) {
// get random integer between 1 and max inclusive on both sides
    double x = ((double) rand()) / RAND_MAX;
    return (int) ceil(x * max);
}

int main() {

    srand( time( NULL) );

    int T[N] = {0};
    T[0] = get_rand_int(10);
    int r = 0;

    for (int i = 1; i < N; i ++) {

        r = get_rand_int(P+1) - 1;
        T[i] = T[i-1] + r;

    }

    printf("Generated array: \n {");
    for (int i = 0; i < N-1; i ++) {
        printf("%d, ", T[i]);
    }

    printf("%d}\n\n", T[N-1]);

    return 0;
}