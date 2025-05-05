/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_enter_leave.c
*/

#include "interface.h"
#include "strace.h"
#include "macro.h"
#include <stdio.h>

/**
 * @brief logs and records function call if symbol address matches.
 * @details scans the symbol table for a matching address.
 *  if a match is found, logs the function entry
 *  and pushes it onto the call stack.
 */
void check_sym(ftrace_t *ftrace, size_t sym, size_t addr, size_t sp)
{
    const char *f_name = NULL;

    for (size_t j = 0; j < ftrace->nm.symbol_count; ++j) {
        if (ftrace->nm.symbols && sym == ftrace->nm.symbols[j].value) {
            f_name = ftrace->nm.symbols[j].name;
            fprintf(stderr, "%sEntering function %s at 0x%lx%s\n",
                GREEN, f_name, addr, RST);
            stack_push_call(&ftrace, addr, f_name, sp);
            break;
        }
    }
}

/**
 * @brief resolves a runtime instruction address to a function call.
 * @details iterates through memory mappings to convert
 * the current RIP into a symbol address. if valid, call check_sym.
 */
void get_func_call(size_t rip, mem_map_t **map, ftrace_t *ftrace,
    size_t sp)
{
    size_t sym = 0;

    if (map == NULL) {
        return;
    }
    for (size_t i = 0; map[i]; ++i) {
        if (rip > map[i]->region[0] && rip < map[i]->region[1]) {
            sym = rip - map[i]->region[0] + map[i]->offset;
            check_sym(ftrace, sym, rip, sp);
        }
    }
}

/**
 * @brief check for return based on stack pointer increasing
 * @details while current stack ptr is greater than the global stack ptr
 * try to pop. if succeed we leaved the function.
 */
void check_for_returns(ftrace_t *ftrace, size_t current_sp)
{
    call_stack_t **gstack = &ftrace->global_stack;
    call_stack_t *call = NULL;

    while (*gstack && current_sp > (*gstack)->stack_ptr) {
        call = stack_pop_call(&ftrace);
        if (call) {
            fprintf(stderr, "%sLeaving function %s%s\n",
                RED, call->func_name ? call->func_name : "unknown", RST);
            stack_free_call(&call);
        }
    }
}
