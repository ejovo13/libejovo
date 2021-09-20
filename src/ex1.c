#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 50

int get_rand_int(int max) {
// get random integer between 1 and max
    double x = ((double) rand()) / RAND_MAX;
    return (int) ceil(x * max);
}

int main() {

    srand( time( NULL ) );

    int arr[N];
    int P = 50;

    printf("Max value P = %d\n", P);

    for(int i = 0; i < N; i ++) {

        arr[i] = get_rand_int(P);

    }

    printf("Elements of arr:\n");
    printf("{");
    for(int i = 0; i < N; i ++) {

        printf("%d, ", arr[i]);
    }
    printf("}\n");


    return 0;
}