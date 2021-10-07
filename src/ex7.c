// Parentheses
#include "ejovo_string.h"

// Return the longest string that is bien parenthesee
char * plus_longue_expr(const char * const __expr_alg) {



}

int main() {

    char exp_alg[] = "(a + x - 2)*(e^x - (2 * 2))+(3)";

    printf("Expression: '%s', reduced: '%s'\n", exp_alg, extract_parentheses(exp_alg)); // extract_parenthesis defined in "ejovo_string.h"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee(exp_alg)); // est_bien_parenthesee defined in "ejovo_string.h"


    return 0;
}