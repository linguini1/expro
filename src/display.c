#include <stdio.h>

#include "poly.h"

static void __expr_print(const expr_t *expr, int wrap);

/*
 * Print a real number.
 * @param The real number to print.
 */
static void real_print(double real) { printf("%f", real); }

/*
 * Print a variable.
 * @param var The variable to print.
 */
static void var_print(const char *var) { printf("%s", var); }

/*
 * Print an operation on two expressions.
 * @param op The operation to print.
 */
static void op_print(const operation_t *op) {

    __expr_print(&op->x, 1);

    switch (op->type) {
    case OP_ADD:
        printf(" + ");
        break;
    case OP_SUB:
        printf(" - ");
        break;
    case OP_MUL:
        printf(" * ");
        break;
    case OP_DIV:
        printf(" / ");
        break;
    case OP_EXP:
        putchar('^');
        break;
    }

    __expr_print(&op->y, 1);
}

/*
 * Print a function.
 * @param func The function to print.
 */
static void func_print(const function_t *func) {
    switch (func->type) {
    case FUNC_SIN:
        printf("sin");
        break;
    case FUNC_COS:
        printf("cos");
        break;
    case FUNC_TAN:
        printf("tan");
        break;
    case FUNC_ATAN:
        printf("atan");
        break;
    case FUNC_LN:
        printf("ln");
        break;
    }
    __expr_print(&func->param, 1);
}

/*
 * Print an expression.
 * @param expr The expression to print.
 * @param wrap Wrap printed expression in parentheses if nonzero.
 */
static void __expr_print(const expr_t *expr, int wrap) {

    if (wrap) putchar('(');

    switch (expr->type) {
    case EXPR_REAL:
        real_print(*((double *)expr->value));
        break;
    case EXPR_VAR:
        var_print(expr->value);
        break;
    case EXPR_OP:
        op_print(expr->value);
        break;
    case EXPR_FUNC:
        func_print(expr->value);
        break;
    }

    if (wrap) putchar(')');
}

/*
 * Print an expression.
 * @param expr The expression to print.
 */
void expr_print(const expr_t *expr) {
    __expr_print(expr, 0);
    putchar('\n');
}

/*
 * Print a substitution table.
 * @param table The substitution table to print.
 */
void substitution_print(const substit_t *table) {
    for (unsigned long i = 0; i < table->len; i++) {
        printf("%s = ", table->entries[i].name);
        __expr_print(&table->entries[i].value, 0);
        putchar('\n');
    }
}
