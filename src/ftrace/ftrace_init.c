/*
** EPITECH PROJECT, 2025
** PSU-ftrace
** File description:
** ftrace_init.c
*/

#include "ftrace.h"
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "utils.h"
#include "parse.h"

static int count_env_var(char **env)
{
    int res = 0;

    for (; env[res]; ++res);
    return 1;
}

static void ftrace_ctor(ftrace_t *ftrace, char *filename, char **env)
{
    ftrace->env = env;
    ftrace->prog = filename;
    ftrace->env_count = count_env_var(env);
    safe_fork(&ftrace->pid);
}

static char *get_filename(const char *restrict path, const ftrace_t *ftrace)
{
    char process_path[PATH_MAX] = {0};

    if (ftrace->flag.p) {
        snprintf(process_path, sizeof(process_path),
            PROC_PATH, ftrace->flag.pid);
        if (!is_executable(process_path)) {
            raise_error("get_filename", "no such PID");
        }
        return strdup(process_path);
    }
    return strdup(path);
}

void ftrace_init(ftrace_t *ftrace, char **env)
{
    ftrace_ctor(ftrace, get_filename(ftrace->prog, ftrace), env);
    switch (ftrace->pid) {
        case 0:
            ftrace_execvp_prog(ftrace);
            break;
        default:
            ftrace_start_tracing(ftrace);
            break;
    }
    free(ftrace->prog);
}
