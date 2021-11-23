#include "ejovo_list.h"

int main() {

    List *list = List_init();
    List_print(list);

    List *clone = List_clone(list);

    List_print(clone);


    return 0;
}