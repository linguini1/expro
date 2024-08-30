#ifndef _POLY_H_
#define _POLY_H_

#include <math.h>

/* Expression types */

typedef enum expr_e {
    EXPR_REAL, /* Real number */
    EXPR_OP,   /* Operation on two expressions */
    EXPR_VAR,  /* Variable with no value yet */
    EXPR_FUNC, /* Function */
} expr_e;

/* Expression structure */

typedef struct {
    expr_e type;
    void *value;
} expr_t;

/* Operation types */

typedef enum {
    OP_ADD, /* Addition (x + y) */
    OP_SUB, /* Subtraction (x - y) */
    OP_MUL, /* Multiplication (xy) */
    OP_DIV, /* Division (x / y) */
    OP_EXP, /* Exponentiation (y^x) */
} operation_e;

/* Operation structure */

typedef struct {
    operation_e type;
    expr_t x; /* x (first) operand */
    expr_t y; /* y (second) operand */
} operation_t;

/* Function which takes a double argument and returns a double */

typedef double(function_f)(double);

/* Function structure */

typedef struct {
    function_f *func;
    expr_t param;
    const char *name;
} function_t;

/* Complex numbers */

typedef struct {
    double re; /* Real component */
    double im; /* Imaginary component */
} complex_t;

/* Variable value table entry */

typedef struct {
    char *name;
    expr_t value;
} entry_t;

/* Variable value table */

typedef struct {
    entry_t *entries;
    unsigned long len;
} substit_t;

/* Stringify text */

#define __stringify(exp) #exp

/* Variable substitution entry */

#define substitution(_name, _value) ((entry_t){.name = (_name), .value = (_value)})

/* Expression builder helpers */

#define __expr(_type, _value)                                                                                          \
    (expr_t) { .type = (_type), .value = &(_value) }

#define e_real(num) __expr(EXPR_REAL, ((complex_t){.re = (num), .im = 0}))
#define e_var(name) __expr(EXPR_VAR, (name))

/* Operation helpers */

#define __op(op, _x, _y) __expr(EXPR_OP, ((operation_t){.type = (op), .x = (_x), .y = (_y)}))

#define o_add(_x, _y) __op(OP_ADD, (_x), (_y))
#define o_sub(_x, _y) __op(OP_SUB, (_x), (_y))
#define o_mul(_x, _y) __op(OP_MUL, (_x), (_y))
#define o_div(_x, _y) __op(OP_DIV, (_x), (_y))
#define o_exp(_x, _y) __op(OP_EXP, (_x), (_y))

/* Function helpers */

#define f_sin(_x) __expr(EXPR_FUNC, ((function_t){.name = "sin", .param = (_x), .func = sin}))
#define f_cos(_x) __expr(EXPR_FUNC, ((function_t){.name = "cos", .param = (_x)}, .func = cos))
#define f_tan(_x) __expr(EXPR_FUNC, ((function_t){.name = "tan", .param = (_x)}, .func = tan))
#define f_atan(_x) __expr(EXPR_FUNC, ((function_t){.name = "atan", .param = (_x), .func = atan}))
#define f_ln(_x) __expr(EXPR_FUNC, ((function_t){.name = "ln", .param = (_x)}, .func = log))
#define f_custom(_f, _x) __expr(EXPR_FUNC, ((function_t){.name = __stringify(_f), .param = (_x), .func = (_f)}))

/* Evaluation */

double expr_eval(const expr_t *expr, const substit_t *values);
void expr_print(const expr_t *expr);
void substitution_print(const substit_t *table);

#endif // _POLY_H_
