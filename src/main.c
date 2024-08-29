#include "poly.h"
#include <stdio.h>

int main(void) {

    substit_t values = {
        .entries =
            (entry_t[]){
                substitution("x", e_real(3.141592653)),
            },
        .len = 1,
    };

    expr_t my_expr = o_add(
        o_exp(
            f_sin(e_var("x")),
            e_real(2)
        ),
        e_real(4)
    );

    // Print expression
    expr_print(&my_expr);

    // Evaluate
    double result = expr_eval(&my_expr, &values);
    printf("Result: %f\n", result);

    return 0;
}
