// Parentheses
#include "ejovo_string.h"

// Return the longest string that is bien parenthesee
char * plus_longue_expr(const char * const __expr_alg)
{
    size_t str_len = strlen(__expr_alg);
    int status = 0; // Variable used to track whether the __expr_alg is currently valid.
    size_t start_index = 0;
    size_t end_index = 0;

    for (size_t i = 0; i < str_len; i ++)
    {
        if( __expr_alg[i] == '(' )
        {
            status ++;
        } else if (__expr_alg[i] == ')')
        {
            status --;
        }



    }
}

int main()
{
    char exp_alg[] = "(a + x - 2)*(e^x - (2 * 2))+(3)";

    printf("Expression: '%s', reduced: '%s'\n", exp_alg, extract_parentheses(exp_alg)); // extract_parenthesis defined in "ejovo_string.h"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee(exp_alg)); // est_bien_parenthesee defined in "ejovo_string.h"

    return 0;
}