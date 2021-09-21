// Ecrire un programme qui g´en`ere un tableau d’entiers de taille N compos´es uniquement de
// 0 et de 1. Les N-1 premiers ´el´ements du tableau sont tir´es au hasard et le dernier ´el´ement est
// la somme des N-1 premier modulo 2.
// Ce proc´ed´e tr`es simple permet de d´etecter certaines erreurs de transmission. Si on veut
// transmettre une s´erie de N-1 bits, on transmet (ce qui est peu co^uteux en m´emoire) N bits en
// ajoutant le bit de parit´e (d´efini pr´ec´edemment). Le recepteur de la s´erie peut ainsi v´erifier si
// la transmission n’a pas introduit d’erreur. Bien entendu certaines erreurs de transmissions se
// compensent et cette m´ethode ne d´etecte pas toutes les erreurs possibles.

#include "ejovo_rand.h"
#include "ejovo_print.h"

#define N 50

int main() {

    ex(8, "Generer un tableau d'entiers [0, 1] de taille N avec le dernier\n\t\telement le bit de parite");

    srand( time( NULL ) );

    int arr[N] = {0};
    int sum = 0;

    for (int i = 0; i < N - 1; i++) {

        arr[i] = get_rand_int_range(0, 1);
        sum += arr[i];
    }

    arr[N-1] = sum % 2;

    print_int_array(arr, N);

    printf("Sum of the first %d elements = %d\n", N-1, sum);

    return 0;
}