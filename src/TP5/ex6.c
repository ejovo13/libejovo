// tri par insertion
#include "ejovo_sort.h"
#include "ejovo_print.h"



int main() {

    ejovo_seed();

    int tab[100] = {0};

    init_tab(100, tab, 100);
    print_int_array(tab, 100);

    printf("Sorting by insertion...\n");
    tri_insertion(tab, 100); // defined in ejovo_sort.c

    print_int_array(tab, 100);

    return 0;
}