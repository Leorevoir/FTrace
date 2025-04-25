/*
** EPITECH PROJECT, 2025
** PSU-ftrace
** File description:
** ftrace_display.c
*/

/**
 * ! Need to specify the path otherwise it get the real syscall.h
 */
#include "../../include/syscall.h"

#include "print.h"
#include "syscall.h"
#include <sys/ptrace.h>
#include <string.h>

static void display_rax_flag_s(ftrace_t *d)
{
    for (int i = 0; print_table[i].func != 0; ++i) {
        if (table[d->regs.orig_rax].return_type == print_table[i].type) {
            fprintf(stderr, "%s\n", print_table[i].func(d->pid, d->regs.rax));
            break;
        }
    }
}

static void display_return(ftrace_t *ftrace)
{
    if (ftrace->regs.orig_rax == EXIT_SIGNAL) {
        fprintf(stderr, "?\n");
        return;
    }
    if (ftrace->flag.s) {
        display_rax_flag_s(ftrace);
        return;
    }
    fprintf(stderr, "0x%llx\n", ftrace->regs.rax);
}

static void s_flag_switch_types(ftrace_t *ftrace, int types, size_t reg)
{
    for (int i = 0; print_table[i].func != 0; ++i) {
        if (types == print_table[i].type && types != STRING) {
            fprintf(stderr, "%s", print_table[i].func(ftrace->pid, reg));
            break;
        }
        if (types == print_table[i].type) {
            fprintf(stderr, "\"%s\"", print_table[i].func(ftrace->pid, reg));
            break;
        }
    }
}

static void display_s_flag(ftrace_t *ftrace)
{
    const size_t registers[] = {
        ftrace->regs.rdi,
        ftrace->regs.rsi,
        ftrace->regs.rdx,
        ftrace->regs.rcx,
        ftrace->regs.r8,
        ftrace->regs.r9
    };
    int *types = get_type_array(ftrace->regs.orig_rax);

    for (int i = 0; i != table[ftrace->regs.orig_rax].arg_count; ++i) {
        s_flag_switch_types(ftrace, types[i], registers[i]);
        if (i < table[ftrace->regs.orig_rax].arg_count - 1) {
            fprintf(stderr, ", ");
        }
    }
    fprintf(stderr, ") = ");
    free(types);
}

static void display_args(ftrace_t *ftrace)
{
    const size_t registers[] = {
        ftrace->regs.rdi,
        ftrace->regs.rsi,
        ftrace->regs.rdx,
        ftrace->regs.rcx,
        ftrace->regs.r8,
        ftrace->regs.r9
    };

    for (int i = 0; i != table[ftrace->regs.orig_rax].arg_count; ++i) {
        fprintf(stderr, "0x%lx", registers[i]);
        if (i != table[ftrace->regs.orig_rax].arg_count - 1) {
            fprintf(stderr, ", ");
        }
    }
    fprintf(stderr, ") = ");
}

static void display_syscalls(ftrace_t *ftrace)
{
    fprintf(stderr, "%s(", table[ftrace->regs.orig_rax].name);
    if (ftrace->regs.orig_rax == EXECVE_SIGNAL) {
        fprintf(stderr, "\"%s\", [\"%s\"], %p /* %d vars */) = ",
            ftrace->prog, ftrace->prog, (void *)ftrace->env,
            ftrace->env_count);
        if (!ftrace->flag.s)
            fprintf(stderr, "0x0\n");
        else
            fprintf(stderr, "0\n");
        return;
    }
    if (ftrace->flag.s) {
        display_s_flag(ftrace);
    } else {
        display_args(ftrace);
    }
    display_return(ftrace);
}

void ftrace_display_trace(ftrace_t *ftrace)
{
    if ((ssize_t)ftrace->regs.orig_rax == -1) {
        return;
    }
    if (ftrace->regs.orig_rax > MAX_SYSCALL) {
        fprintf(stderr, "Unknown\n");
        return;
    }
    display_syscalls(ftrace);
    if (ftrace->regs.orig_rax == EXIT_SIGNAL) {
        fprintf(stderr, "+++ exited with %lld +++\n", ftrace->regs.rdi);
    }
}
