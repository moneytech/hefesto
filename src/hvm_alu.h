/*
 *            Copyright (C) 2013, 2014, 2015, 2016 by Rafael Santiago
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#ifndef HEFESTO_HVM_ALU_H
#define HEFESTO_HVM_ALU_H 1

#include "types.h"
#include "expr_handler.h"

void *expr_eval(char *expr,
                hefesto_var_list_ctx **lo_vars,
                hefesto_var_list_ctx **gl_vars,
                hefesto_func_list_ctx *functions,
                hefesto_type_t *etype, size_t *outsz);

hefesto_type_t get_last_evaluated_type();

hefesto_type_t get_last_evaluated_subtype();

#endif  // HEFESTO_HVM_ALU_H
