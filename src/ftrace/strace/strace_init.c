/*
** EPITECH PROJECT, 2025
** PSU-ftrace
** File description:
** ftrace_init.c
*/

#include "ftrace.h"
#include "shared_lib.h"

static size_t count_env_var(char **env)
{
    size_t res = 0;

    for (; env[res]; ++res);
    return 1;
}

void init_strace(strace_t *strace, char **env, const char *restrict filename)
{
    strace->env = env;
    strace->prog = filename;
    strace->env_count = count_env_var(env);
    strace->flag.s = true;
    strace->is_first = true;
    safe_fork(&strace->pid);
}
