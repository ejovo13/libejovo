// Tri rapide
#include "ejovo_sort.h"
#include "ejovo_print.h"

int *nouveau_tableau(int __length) {

    int *arr = (int *) malloc(sizeof(int) * __length);
    return arr;

}

void detruire_tableau(int *tab) {
    free(tab);
}


// concatenate two integer arrays where __arr1 will go on the left and __arr2 will go on the right
int *arrcat(const int *__arr1, const int *__arr2, const int __len1, const int __len2 ) {
    const int cat_len = __len1 + __len2;
    int *cat = (int *) malloc(sizeof(int) * (cat_len));
    int lower_i = 0;
    int upper_i = 0;

    // ideally this should be split up into two for loops but you've imposed a time restraint for these exercises
    for (int i = 0; i < cat_len; i++) {

        if ( i < __len1 ) {

            cat[i] = __arr1[lower_i];
            lower_i ++;
        } else {

            cat[i] = __arr2[upper_i];
            upper_i ++;
        }
    }

    return cat;
}

// append a value __n_repetitions times to the end of __arr
int *append_value(int *__arr, const int __len, const int __value, const int __n_repetitions) {

    const int cat_len = __len + __n_repetitions;
    int *cat = (int *) malloc(sizeof(int) * cat_len);

    for (int i = 0; i < cat_len; i++) {
        if (i < __len) {
            cat[i] = __arr[i];
        } else {
            cat[i] = __value;
        }
    }

    return cat;

}

// return
int *tri_rapide(int *__tab, int __n, int __pivot_index, int *__n_inf_ptr, int *__n_sup_ptr, int *__n_eq_ptr) {

    int n_inf = 0;
    int n_sup = 0;
    int n_eq = 0;
    bool is_homogeneous = false; // true if all elements are the same integer
    printf("Called tri_rapide with n: %d\n", __n);
    print_int_array(__tab, __n);

    // count the number of inferior and superior elements
    for (int i = 0; i < __n; i++) {
        if (__tab[i] < __tab[__pivot_index]) {
            n_inf++;
        } else if (__tab[i] > __tab[__pivot_index]) {
            n_sup++;
        } else {
            n_eq++;
        }
    }


    is_homogeneous = (n_inf == 0 && n_sup == 0);

    // n_inf = n_inf + n_eq; // now change to less than or equal to
    *__n_inf_ptr = n_inf;
    *__n_sup_ptr = n_sup;
    *__n_eq_ptr  = n_eq;

    int *inf_arr = NULL;
    int *sup_arr = NULL;

    if (!is_homogeneous) { // if doesnt contain only one element, split it up

        if (n_inf > 0) {
            inf_arr = nouveau_tableau(n_inf);

            // now fill this inferior array
            int inf_i = 0; // inferior array index

            for (int i = 0; i < __n; i++) {

                if (__tab[i] < __tab[__pivot_index]) {

                    inf_arr[inf_i] = __tab[i];
                    inf_i ++;
                }
            }

            int n_sup_dummy = 0; // dummy variable


            int n_eq_dummy = 0;
            inf_arr = tri_rapide(inf_arr, n_inf, 0, &n_inf, &n_sup_dummy, &n_eq_dummy);
            inf_arr = append_value(inf_arr, n_inf, __tab[__pivot_index], n_eq_dummy);
            printf("Append value '%d' %d times to the end of inf\n", __tab[__pivot_index], n_eq_dummy);

        }

        if (n_sup > 0) {
            sup_arr = nouveau_tableau(n_sup);

            // now fill this superior array
            int sup_i = 0; // superior array index

            for (int i = 0; i < __n; i++) {

                if (__tab[i] > __tab[__pivot_index]) {

                    sup_arr[sup_i] = __tab[i];
                    sup_i ++;
                }
            }

            int n_inf_dummy = 0; // dummy variable
            int n_eq_dummy2 = 0;

            sup_arr = tri_rapide(sup_arr, n_sup, 0, &n_inf_dummy, &n_sup, &n_eq_dummy2);
        }

        if(n_inf == 0 && n_sup == 0) {
            printf("Concatenated inf_arr and sup_arr:\n");
            return __tab;
        } else if (n_inf + n_eq > 0) {
            return inf_arr;
        } else if (n_sup > 0) {
            return sup_arr;
        } else {
            perror("you fucked up bro");
            return NULL;
        }


    } else { // if the array that we are dealing with is homogeneous, then return the array

        printf("Returning tab: %p\n", __tab);
        print_int_array(__tab, __n);
        return __tab;

    }
}





int main() {

    ejovo_seed();


    int c[5] = {61, 21, 40, 84, 74};
    // init_tab(100, c, 5);

    print_int_array(c, 5);

    int dummy1 = 0;
    int dummy2 = 0;
    int dummy3 = 0;

    int *sorted = tri_rapide(c, 5, 0, &dummy1, &dummy2, &dummy3);
    // print_int_array(sorted, 1);
    printf("Sorted address: %p", sorted);


    return 0;
}
