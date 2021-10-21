// Ecrire une fonction affiche_tab

#include <stdbool.h>
#include <ejovo_print.h>



int main() {

    int tab[] = {1, 2, 3, 25, 2345, 5467, 254, 6548, 245, 35647, 2345, 4567};

    // print_int_array declared in `ejovo_print.h` and defined in `ejovo_print.c`
    print_int_array(tab, 3);
    print_int_array(tab, 5);
    print_int_array(tab, 10);
    print_int_array(tab, 12);


    return 0;
}
