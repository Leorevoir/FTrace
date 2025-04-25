/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** ftrace.h
*/

#ifndef FTRACE_H_H
    #define FTRACE_H_H

    #include "macro.h"
    #include "utils.h"
    #include <sys/types.h>
    #include <sys/user.h>

    #define     MAX_SYSCALL     (328)
    #define     EXIT_SIGNAL     (231)
    #define     EXECVE_SIGNAL   (59)
    #define     MAX_BUFFER      (4096)
    #define     PROC_PATH       ("/proc/%d/exe")

typedef struct flag_s {
    bool p;
    pid_t pid;
    bool s;
} flag_t;

/*
 * global ftrace struct
 */
typedef struct ftrace_s {
    pid_t pid;
    char **env;
    flag_t flag;
    char *prog;
    struct user_regs_struct regs;
    int env_count;
} ftrace_t;

/*
 * safer
 */
void safe_waitpid(pid_t pid, int *stat_loc, int options);
void safe_fork(pid_t *pid);

/*
 * main entry point
 */
void ftrace_init(ftrace_t *ftrace, char **env);

/*
 * ptrace and execvp program
 */
void ftrace_execvp_prog(ftrace_t *ftrace);

/*
 * trace program and display syscalls
 */
void ftrace_start_tracing(ftrace_t *ftrace);
void ftrace_display_trace(ftrace_t *ftrace);

/*
 * tools
 */
int *get_type_array(size_t id);
void free_char(char **ptr);

#endif /* FTRACE_H_H */
