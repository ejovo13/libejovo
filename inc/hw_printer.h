// Provide a few functions to print the description of an exercise
#include <stdio.h>

void print_line(int num_chars, char  border_char) {

    for(int i = 0; i < num_chars; i++) {
        printf("%c", border_char);
    }
    printf("\n");

}

void ex(int __ex_num, char * __description) {

    print_line(80, '=');
    printf("\t\t\t\t   Exercise %d \n", __ex_num);
    print_line(80, '=');
    printf("Description:\t%s \n", __description);
    print_line(80, '=');
    printf("\n\n");

}
