// Ecrire une fonction incremente qui prend 3 parametres en entree (__a, __b, et __i) et qui
// ajoute a __a et __b la valeur __i. Cette fonction retourne la valeur 1 si __i vaut 0, 0 sinon.

#include <stdbool.h>

bool incremente(int * __aptr, int * __bptr, int __i) {

    *__aptr += __i;
    *__bptr += __i;

    return __i == 0;

}