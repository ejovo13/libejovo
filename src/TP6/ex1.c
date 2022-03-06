// D´efinir un type de donn´ee liste dont chaque maillon est compos´e d’un nombre flottant c en
// double pr´ecision et d’un entier n.
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {

    double c;
    int n;
    struct node_t *next;

} Node;

int main() {

    Node n = {.c = 1.2, .n = 0, .next = 0}; // badass way to initialize structures

    printf("n.c: %lf\n", n.c);
    printf("n.n: %d\n", n.n);
    printf("n.next: %p\n", n.next);


}

