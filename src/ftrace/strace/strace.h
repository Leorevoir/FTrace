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

void strace_run(ftrace_t *ftrace);
bool strace_handle_signals(int *stat_loc, pid_t __attribute__((unused))*pid);

/*
 * memory safe clean
 */
void clean_map(mem_map_t ***map);
void clean_stack(ftrace_t **ftrace);

/*
* get function enter-leave
*/
void check_sym(ftrace_t *ftrace, size_t sym, size_t addr,
    size_t sp);
void get_func_call(size_t rip, mem_map_t **map, ftrace_t *ftrace,
    size_t sp);
void check_for_returns(ftrace_t *ftrace, size_t current_sp);


/*
* call stack
*/
void stack_free_call(call_stack_t **call);
call_stack_t *stack_pop_call(ftrace_t **ftrace);
void stack_push_call(ftrace_t **ftrace, size_t addr,
    const char *restrict func_name, size_t ptr);

#endif /* FTRACE_STRACE_H_H */
