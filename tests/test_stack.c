/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** test_stack.c
*/

#include "unit-tests.h"
#include "interface.h"
#include "shared_lib.h"
#include <src/ftrace/strace/strace.h>

void stack_push_call(ftrace_t **ftrace, size_t addr,
    const char *restrict func_name, size_t ptr);
call_stack_t *stack_pop_call(ftrace_t **ftrace);
void stack_free_call(call_stack_t **call);

Test(stack_free_call, test_stack_free_call)
{
    call_stack_t *call = NULL;

    stack_free_call(&call);
    cr_assert_null(call);
}

Test(stack_push_call, test_stack_push_call)
{
    ftrace_t *ftrace = NULL;
    call_stack_t *call = NULL;

    safe_alloc((Object_t **)&ftrace, sizeof(ftrace_t));
    cr_assert_not_null(ftrace);
    stack_push_call(&ftrace, 0x12345678, "test_func", 0x87654321);
    call = stack_pop_call(&ftrace);
    cr_assert_eq(call->addr, 0x12345678);
    cr_assert_str_eq(call->func_name, "test_func");
    cr_assert_eq(call->stack_ptr, 0x87654321);
    stack_free_call(&call);
    safe_free((Object_t **)&ftrace);
}

Test(stack_pop_call, test_stack_pop_call)
{
    ftrace_t *ftrace = NULL;
    call_stack_t *call = NULL;

    safe_alloc((Object_t **)&ftrace, sizeof(ftrace_t));
    cr_assert_not_null(ftrace);
    stack_push_call(&ftrace, 0x12345678, "test_func", 0x87654321);
    call = stack_pop_call(&ftrace);
    cr_assert_eq(call->addr, 0x12345678);
    cr_assert_str_eq(call->func_name, "test_func");
    cr_assert_eq(call->stack_ptr, 0x87654321);
    stack_free_call(&call);
    safe_free((Object_t **)&ftrace);
}
