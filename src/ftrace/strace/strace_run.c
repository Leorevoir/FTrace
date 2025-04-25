/*
** EPITECH PROJECT, 2025
** PSU-ftrace
** File description:
** strace_run.c
*/

#include "strace.h"

void strace_run(strace_t *strace)
{
    switch (strace->pid) {
        case 0:
            strace_execvp_prog(strace);
            break;
        default:
            strace_start_tracing(strace);
            break;
    }
}
