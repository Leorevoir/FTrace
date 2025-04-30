/*
** EPITECH PROJECT, 2025
** PSU-ftrace
** File description:
** strace_run.c
*/

#include "strace.h"

void strace_run(ftrace_t *ftrace)
{
    switch (ftrace->strace.pid) {
        case 0:
            strace_execvp_prog(&ftrace->strace);
            break;
        default:
            strace_start_tracing(ftrace);
            break;
    }
}
