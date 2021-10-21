#include <stdio.h>

int main() {

    int a = 2;
    int b = a++;

    printf("A = %d, B = %d\n", a, b);

    a = 2;
    b = ++a;

    printf("A = %d, B = %d\n", a, b);

    return 0;

}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}
