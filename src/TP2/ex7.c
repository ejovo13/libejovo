// Cet exercice consiste `a m´elanger les ´el´ements d’un tableau tri´e. On pourra utiliser le tableau
// tri´e g´en´er´e dans l’exercice pr´ec´edent. La proc´edure de m´elange (appel´e algorithme de FisherYates) consiste `a parcourir le tableau T et, pour chaque indice i, `a ´echanger l’´el´ement T[i]
// avec un ´el´ement tir´e au hasard situ´e apr`es (c’est `a dire dont l’indice j est tel que j>i).

#include "ejovo_print.h"
#include "ejovo_rand.h"

#define N 50
#define P 3

int main() {

    ex(7, "Melanger les elements dun tableau trie");

    srand( time( NULL) );

    int T[N] = {0};
    T[0] = get_rand_int(10);
    int r = 0;

    // generate random matrix from exercise 4.
    for (int i = 1; i < N; i ++) {

        r = get_rand_int(P+1) - 1;
        T[i] = T[i-1] + r;

    }

    printf("Generated array: \n");
    print_int_array(T, N);


    int j = 0;
    int temp = 0;

    // Now scramble the array with Fisher-Yates algorithm
    for (int i = 0; i < N - 1; i ++) {

        j = get_rand_int_range(i + 1, N - 1); // get random int in [i + 1, N - 1]

        temp = T[i];
        T[i] = T[j];
        T[j] = temp;

    }

    printf("Scrambled array: \n");
    print_int_array(T, N);

    return 0;
}