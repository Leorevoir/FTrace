/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** ftrace_stack.c
*/

#include "interface.h"
#include "shared_lib.h"
#include <string.h>
#include <stdlib.h>

void stack_push_call(ftrace_t **ftrace, size_t addr,
    const char *restrict func_name, size_t ptr)
{
    call_stack_t *new_call = NULL;

    if (!ftrace || !*ftrace) {
        return;
    }
    safe_alloc((Object_t **)&new_call, sizeof(call_stack_t));
    if (!new_call) {
        return;
    }
    new_call->addr = addr;
    new_call->func_name = func_name ? strdup(func_name) : NULL;
    new_call->stack_ptr = ptr;
    new_call->next = (*ftrace)->global_stack;
    (*ftrace)->global_stack = new_call;
}

call_stack_t *stack_pop_call(ftrace_t **ftrace)
{
    call_stack_t *call = NULL;

    if (!ftrace || !*ftrace || !(*ftrace)->global_stack) {
        return NULL;
    }
    call = (*ftrace)->global_stack;
    (*ftrace)->global_stack = call->next;
    call->next = NULL;
    return call;
}

void stack_free_call(call_stack_t **call)
{
    if (!call || !*call) {
        return;
    }
    if ((*call)->func_name) {
        safe_free((Object_t **)&((*call)->func_name));
        (*call)->func_name = NULL;
    }
    safe_free((Object_t **)&(*call));
    *call = NULL;
}
