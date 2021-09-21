#include "ejovo_print.h"
#include "ejovo_rand.h"

#define N 50

int main() {

    ex(1, "Initialise un tableau de taille N avec des entiers entre 1 et P");

    srand( time( NULL ) );

    int arr[N];
    int P = 50;

    printf("Max value P = %d\n", P);

    for(int i = 0; i < N; i ++) {

        arr[i] = get_rand_int(P);

    }

    printf("Elements of arr:\n");
    print_int_array(arr, N);


    return 0;
}