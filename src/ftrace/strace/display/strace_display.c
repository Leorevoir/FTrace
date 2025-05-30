/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_display.c
*/

#include "ftrace_syscall.h"
#include <sys/ptrace.h>
#include <string.h>
#include <stdio.h>
#include "../strace.h"
#include "shared_lib.h"

static void display_rax_flag_s(strace_t *d)
{
    char __attribute__((cleanup(safe_free_char)))*tmp = NULL;

    for (int i = 0; print_table[i].func != 0; ++i) {
        if (table[d->regs.orig_rax].return_type == print_table[i].type) {
            tmp = print_table[i].func(d->pid, d->regs.rax);
            fprintf(stderr, "%s\n", tmp);
            break;
        }
    }
}

static void display_return(strace_t *strace)
{
    if (strace->regs.orig_rax == EXIT_SIGNAL) {
        fprintf(stderr, "?\n");
        return;
    }
    if (strace->flag.s) {
        display_rax_flag_s(strace);
        return;
    }
    fprintf(stderr, "0x%llx\n", strace->regs.rax);
}

static void s_flag_switch_types(strace_t *strace, int type, size_t reg)
{
    char __attribute__((cleanup(safe_free_char)))*tmp = NULL;

    for (size_t i = 0; print_table[i].func != 0; ++i) {
        if (type == print_table[i].type && (type == VOID_P || type == VOID)) {
            fprintf(stderr, "%s", print_table[i].func(strace->pid, reg));
            break;
        }
        if (type == print_table[i].type && type != STRING) {
            tmp = print_table[i].func(strace->pid, reg);
            fprintf(stderr, "%s", tmp);
            break;
        }
        if (type == print_table[i].type) {
            tmp = print_table[i].func(strace->pid, reg);
            fprintf(stderr, "\"%s\"", tmp);
            break;
        }
    }
}

static void display_s_flag(strace_t *strace)
{
    const size_t registers[] = {
        strace->regs.rdi,
        strace->regs.rsi,
        strace->regs.rdx,
        strace->regs.rcx,
        strace->regs.r8,
        strace->regs.r9
    };
    int *types = get_type_array(strace->regs.orig_rax);

    for (int i = 0; i != table[strace->regs.orig_rax].arg_count; ++i) {
        s_flag_switch_types(strace, types[i], registers[i]);
        if (i < table[strace->regs.orig_rax].arg_count - 1) {
            fprintf(stderr, ", ");
        }
    }
    fprintf(stderr, ") = ");
    free(types);
}

static void display_args(strace_t *strace)
{
    const size_t registers[] = {
        strace->regs.rdi,
        strace->regs.rsi,
        strace->regs.rdx,
        strace->regs.rcx,
        strace->regs.r8,
        strace->regs.r9
    };

    for (int i = 0; i != table[strace->regs.orig_rax].arg_count; ++i) {
        fprintf(stderr, "0x%lx", registers[i]);
        if (i != table[strace->regs.orig_rax].arg_count - 1) {
            fprintf(stderr, ", ");
        }
    }
    fprintf(stderr, ") = ");
}

static void display_syscalls(strace_t *strace)
{
    fprintf(stderr, "Syscall %s(", table[strace->regs.orig_rax].name);
    if (strace->regs.orig_rax == EXECVE_SIGNAL) {
        fprintf(stderr, "\"%s\", [\"%s\"], %p /* %ld vars */) = ",
            strace->prog, strace->prog, (void *)strace->env,
            strace->env_count);
        if (!strace->flag.s)
            fprintf(stderr, "0x0\n");
        else
            fprintf(stderr, "0\n");
        return;
    }
    if (strace->flag.s) {
        display_s_flag(strace);
    } else {
        display_args(strace);
    }
    display_return(strace);
}

void strace_display_trace(strace_t *strace)
{
    if ((ssize_t)strace->regs.orig_rax == -1) {
        return;
    }
    if (strace->regs.orig_rax > MAX_SYSCALL) {
        fprintf(stderr, "Unknown\n");
        return;
    }
    display_syscalls(strace);
    if (strace->regs.orig_rax == EXIT_SIGNAL) {
        fprintf(stderr, "+++ exited with %lld +++\n", strace->regs.rdi);
    }
}
