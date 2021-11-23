#include "ejovo_list.h"

int main() {

    // List *list = List_new();

    // double a[] = {0, 3, 1};

    // Polynome *poly = Polynome_new(a, 3);

    // List_print(poly);

    // double x = 10;

    // Polynome_print(poly);

    // // Polynome *polyk = List_clone(poly);
    // // List_print(polyk);
    // // polymult_k(polyk, 3);
    // // List_print(polyk);
    // // polymult_k(polyk, 3);
    // // List_print(polyk);

    // Polynome *polyk = Polynome_mult_k(poly, 3);

    // Polynome_print(polyk);

    // List_print(poly);
    // List_print(polyk);



    // printf("p(%lf) = %lf\n", x, Polynome_eval(poly, x));
    // printf("p9(%lf) = %lf\n", x, Polynome_eval(polyk, x));

    printf("==============\n");

    Polynome *f1 = Polynome_new((double[2]) {-2, 1}, 2);
    Polynome *f2 = Polynome_new((double[2]) {-6, 1}, 2);

    printf("f1:\n");
    List_print(f1);
    printf("f2:\n");
    List_print(f2);

    Polynome_print(f1);
    Polynome_print(f2);

    Node *f2_head = f2->head;

    printf("Inserting f2_head\n");
    // List_ordered_insert_n(f1, f2_head);
    // List_print(f1);
    // List_ordered_insert_n(f1, f2_head->next);
    // f1 = Polynome_sum(f1, f2);
    List_print(f1);
    List_print(f2);
    // List_print(Polynome_sum(f1, f1));
    // List_print(f1);
    // List_print(Polynome_mult_monome(f1, f2->head->next));

    List_print(Polynome_mult_poly(f1, f2));

    Polynome *zero = Polynome_zeros(10);

    Polynome_print(zero);


    // Polynome_print(f1p2);


    // Polynome *f12 = polymultpoly(f1, f2);

    // Polynome_print(f12);


    // while (true) {

    //     long long int input = 0;

    //     scanf("%ld", &input);

    //     printf("factorial(%ld) := %lld\n", input, ejovo_fact(input));


    // }

    // Polynome *exp15 = Polynome_exp(15);

    // Polynome_print(exp15);

    // printf("exp(3) = %lf\n", Polynome_eval(exp15, 3));

    Polynome **exp_arr = (Polynome **) malloc(sizeof(Polynome) * 25);

    for (size_t i = 1; i <= 25; i++) {

        exp_arr[i] = Polynome_exp(i);
        printf("exp%d(-4) -> %lf\n", i, Polynome_eval(exp_arr[i], -4));

    }

    Polynome *sin10 = Polynome_sin(10);

    Polynome_print(sin10);

    Polynome *cos5 = Polynome_cos(5);
    Polynome_print(cos5);





    return 0;
}