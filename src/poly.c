#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "poly.h"

/* Private function prototypes */
static double __expr_eval(const expr_t *expr, const substit_t *values);
static double op_eval(const operation_t *op, const substit_t *values);
static double var_get_val(const char *name, const substit_t *values);
static double func_eval(const function_t *func, const substit_t *values);

/*
 * Evaluate an expression to its final form.
 * @param expr The expression to evaluate.
 * @return The final value of the evaluated expression.
 */
static double __expr_eval(const expr_t *expr, const substit_t *values) {
    switch (expr->type) {
    case EXPR_REAL:
        return *((double *)expr->value);
    case EXPR_OP:
        return op_eval(expr->value, values);
    case EXPR_VAR:
        return var_get_val(expr->value, values);
    case EXPR_FUNC:
        return func_eval(expr->value, values);
    }
    assert(0);
}

static double op_eval(const operation_t *op, const substit_t *values) {
    switch (op->type) {
    case OP_ADD:
        return __expr_eval(&op->x, values) + __expr_eval(&op->y, values);
    case OP_SUB:
        return __expr_eval(&op->x, values) - __expr_eval(&op->y, values);
    case OP_MUL:
        return __expr_eval(&op->x, values) * __expr_eval(&op->y, values);
    case OP_DIV:
        return __expr_eval(&op->x, values) / __expr_eval(&op->y, values);
    case OP_EXP:
        return pow(__expr_eval(&op->x, values), __expr_eval(&op->y, values));
    }
    assert(0);
}

/*
 * Get the value of a variable.
 * @param name The name of the variable.
 * @param values The table of variable values.
 * @return The value of the variable.
 */
static double var_get_val(const char *name, const substit_t *values) {
    for (unsigned long i = 0; i < values->len; i++) {
        if (!strcmp(name, values->entries[i].name)) {
            return __expr_eval(&values->entries[i].value, values);
        }
    }
    assert(0); // There should never be a failed variable lookup
}

/*
 * Evaluates a function.
 * @param func The function to evaluate.
 * @param values The variable values to substitute variables.
 * @return The result of evaluating the function.
 */
static double func_eval(const function_t *func, const substit_t *values) {
    switch (func->type) {
    case FUNC_SIN:
        return sin(__expr_eval(&func->param, values));
    case FUNC_COS:
        return cos(__expr_eval(&func->param, values));
    case FUNC_TAN:
        return tan(__expr_eval(&func->param, values));
    case FUNC_ATAN:
        return atan(__expr_eval(&func->param, values));
    case FUNC_LN:
        return log(__expr_eval(&func->param, values));
    }
    assert(0);
}

/*
 * Evaluate an expression.
 * @param expr The expression to evaluate.
 * @return The evaluated result of the expression.
 */

double expr_eval(const expr_t *expr, const substit_t *values) { return __expr_eval(expr, values); }
