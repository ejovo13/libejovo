#include "ejovo_list.h"

int main() {

    List *l = List_new();
    Node *n = Node_new(3.2, 1);

    List_append_new_node(l, 1.234, 2);
    List_prepend_node(l, n);
    List_append_new_node(l, 129.2, 3);
    List_prepend_new_node(l, -913.134, 0);
    List_append_new_node(l, 12, 15);
    List_append_new_node(l, 28, 28);

    List_print(l);

    printf("Adding a new node with n = 17");

    Node *n1 = Node_new(17, 17);
    List_ordered_insert_n(l, n1);

    List_print(l);

    printf("Adding n = 10\n");
    List_ordered_insert_n(l, Node_new(10, 10));

    printf("Adding n = 39\n");
    List_ordered_insert_n(l, Node_new(39, 39));

    printf("Adding duplicate value for n = 15\n");

    List_ordered_insert_n(l, Node_new(-10, 15));
    List_ordered_insert_n(l, Node_new(-100, 3));

    printf("Adding duplicate value for n = 3\n");

    List_print(l);

    // printf("REMOVING LAST ELEMENT\n");
    // List_remove_last(l);

    // List_print(l);

    // modification_valeur(l->head, 5);

    // List_print(l);

    // printf("REMOVING FIRST ELEMENT\n");
    // List_remove_first(l);

    // List_print(l);

    // printf("REMOVING FIRST ELEMENT\n");
    // List_remove_first(l);

    // List_print(l);

    // printf("REMOVING LAST ELEMENT\n");
    // List_remove_last(l);

    // List_print(l);

    // List_append_new_node(l, 1.45, 10);

    // List_print(l);

    // List_remove_first(l);

    // printf("REMOVING FIRST ELEMENT\n");

    // List_print(l);


    return 0;
}