#include "ejovo_list.h"

int main() {

    List *list = List_init();
    List_print(list);

    List *clone = List_clone(list);

    Node_print(Node_clone(list->head));

    Node_print(clone->head);

    List_print(clone);


    return 0;
}