#include "ejovo_print.h"

void print_line(int num_chars, char  border_char) {
// print a line whose width is 'num_chars' using the character 'border_char'
    for(int i = 0; i < num_chars; i++) {
        printf("%c", border_char);
    }
    printf("\n");

}

void ex(int __ex_num, char * __description) {
// print a simple summary of exercise number '__ex_num' when given description '__description'
    print_line(80, '=');
    printf("\t\t\t\t   Exercise %d \n", __ex_num);
    print_line(80, '=');
    printf("Description:\t%s \n", __description);
    print_line(80, '=');
    printf("\n\n");

}

void print_int_array(int * __arr, int __n) {
// print array '__arr' of '__n' integers
    printf("{");
    for (int i = 0; i < __n-1; i ++) {
        printf("%d, ", __arr[i]);
    }
    printf("%d}\n\n", __arr[__n-1]);

}