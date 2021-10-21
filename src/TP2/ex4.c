// generer un tablue d'entiers T de taille N dans l'ordre croissant
// premier element est un entier aleatoire compris entre 1 et 10.
// T[i] = T[i-1] + r, avec r un entier aleatoire compris entre 0 et P

#include "ejovo_print.h"
#include "ejovo_rand.h"

#define N 50
#define P 3



int main() {

    ex(4, "Generer un tableau d'entiers N dans l'ordre croissant");

    srand( time( NULL) );

    int T[N] = {0};
    T[0] = get_rand_int(10);
    int r = 0;

    for (int i = 1; i < N; i ++) {

        r = get_rand_int(P+1) - 1;
        T[i] = T[i-1] + r;

    }

    printf("Generated array: \n");
    print_int_array(T, N);

    return 0;
}