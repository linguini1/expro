# poly

Just a silly bunch of preprocessor macros for creating mathematical expressions in C.

# Usage

Use the macro API to create a bunch of expressions.

```c
// The expression: (sin(x))^2 + 4
expr_t my_expr = o_add(
    o_exp(
        f_sin(e_var("x")),
        e_real(2)
    ),
    e_real(4)
);
```

Print the expression using `expr_print` to see your expression and verify that it's correct.

```c
expr_print(&my_expr);
// ((sin(x))^(2.000000)) + (4.000000)
```

Evaluate the expression using `expr_eval`, passing in a table of values to substitute variables with. You can substitute
variables with expressions as well.

```c
substit_t values = {
    .entries =
        (entry_t[]){
            substitution("x", e_real(3.141592653)),
        },
    .len = 1,
};

double result = expr_eval(&my_expr, &values);
printf("Result: %f\n", result);
// Result: 4.000000
```
