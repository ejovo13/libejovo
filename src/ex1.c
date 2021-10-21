// Ecrire une fonction incremente qui prend 3 parametres en entree (__a, __b, et __i) et qui
// ajoute a __a et __b la valeur __i. Cette fonction retourne la valeur 1 si __i vaut 0, 0 sinon.

#include <stdbool.h>
#include <stdio.h>

bool incremente(int *restrict __aptr, int *restrict __bptr, int __i) {

    *__aptr += __i;
    *__bptr += __i;

    return __i == 0;

}

int main() {

    int a = 0;
    int b = 100;
    int i = 5;

    incremente(&a, &b, i);
    printf("a incremented by %d: %d\n", i, a);
    printf("b incremented by %d: %d\n", i, b);

}