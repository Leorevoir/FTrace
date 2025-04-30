/*
** EPITECH PROJECT, 2025
** strace
** File description:
** strace.h
*/

#ifndef FTRACE_STRACE_H_H
    #define FTRACE_STRACE_H_H

    #include <stdbool.h>
    #include "interface.h"


    #define     MAX_SYSCALL     (328)
    #define     EXIT_SIGNAL     (231)
    #define     EXECVE_SIGNAL   (59)
    #define     MAX_BUFFER      (4096)
    #define     PROC_PATH       ("/proc/%d/exe")

/*
 * ptrace and execvp program
 */
void strace_execvp_prog(strace_t *strace);

/*
 * trace program and display syscalls
 */
void strace_start_tracing(ftrace_t *ftrace);
void strace_display_trace(strace_t *strace);

/*
 * tools
 */
int *get_type_array(size_t id);
void free_char(char **ptr);

void strace_run(ftrace_t *ftrace);

#endif /* FTRACE_STRACE_H_H */
