/*
** EPITECH PROJECT, 2025
** PSU-ftrace
** File description:
** ftrace_start.c
*/

#include "ftrace.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

void ftrace_execvp_prog(ftrace_t *ftrace)
{
    if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) {
        raise_error("ftrace_execvp_prog", "ptrace failed");
    }
    if (execvp(ftrace->prog, (char **)&ftrace->prog) == -1) {
        raise_error("ftrace_execvp_prog", "execvp failed");
    }
}

void ftrace_start_tracing(ftrace_t *ftrace)
{
    int stat_loc = 0;

    safe_waitpid(ftrace->pid, &stat_loc, 0);
    if (ptrace(
        PTRACE_SETOPTIONS, ftrace->pid, NULL, PTRACE_O_TRACEEXIT) == -1) {
        perror("ptrace");
    }
    while (!WIFEXITED(stat_loc)) {
        if (ptrace(PTRACE_GETREGS, ftrace->pid, NULL, &ftrace->regs) == -1) {
            perror("ptrace");
        }
        ftrace_display_trace(ftrace);
        if (ptrace(PTRACE_SINGLESTEP, ftrace->pid, NULL, 0) == -1) {
            perror("ptrace");
        }
        safe_waitpid(ftrace->pid, &stat_loc, 0);
    }
}
