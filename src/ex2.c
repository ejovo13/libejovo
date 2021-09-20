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

    printf("Generating array of length %d with max value %d...\n", N, P);

    for(int i = 0; i < N; i ++) {

        arr[i] = get_rand_int(P);

    }

    printf("\nPlease enter a positive integer <= %d\n\n", P);
    printf("n = ");

    int n = -1;
    int index = -1;

    scanf("%d", &n);

    for (int i = 0; i < N; i ++) {

        if (arr[i] == n) {
            index = i;
            break;
        } else {
            continue;
        }
    }

    if (index == -1) {
        printf("\nn not found\n\n");
    } else {
        printf("\nFirst index of n: %d\n\n", index);
    }

    printf("Elements of arr:\n");
    printf("{");
    for(int i = 0; i < N; i ++) {

        printf("%d, ", arr[i]);
    }
    printf("}\n");


    return 0;
}