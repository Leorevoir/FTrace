/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_start.c
*/

#include "parse.h"
#include "strace.h"
#include "shared_lib.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void check_sym(ftrace_t *ftrace, unsigned long sym, unsigned long addr)
{
    for (size_t j = 0; j < ftrace->nm.symbol_count; ++j) {
        if (ftrace->nm.symbols && sym == ftrace->nm.symbols[j].value) {
            fprintf(stderr, "Entering function %s at 0x%lx\n",
                ftrace->nm.symbols[j].name, addr);
            break;
        }
    }
}

static void get_func_call(unsigned long rip, mem_map_t **map, ftrace_t *ftrace)
{
    unsigned long sym = 0;

    if (map == NULL) {
        return;
    }
    for (size_t i = 0; map[i]; ++i) {
        if (rip > map[i]->region[0] && rip < map[i]->region[1]) {
            sym = rip - map[i]->region[0] + map[i]->offset;
            check_sym(ftrace, sym, rip);
        }
    }
}

void strace_execvp_prog(strace_t *strace)
{
    if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) {
        raise_error("strace_execvp_prog", "ptrace failed");
    }
    if (execvp(strace->prog, (char **)&strace->prog) == -1) {
        raise_error("strace_execvp_prog", "execvp failed");
    }
}

void loop(int stat_loc, ftrace_t *ftrace, mem_map_t **map)
{
    while (!WIFEXITED(stat_loc)) {
        if (ptrace(PTRACE_GETREGS, ftrace->strace.pid, NULL,
            &ftrace->strace.regs) == -1) {
            perror("ptrace");
            break;
        }
        get_func_call(ftrace->strace.regs.rip, map, ftrace);
        strace_display_trace(&ftrace->strace);
        if (ptrace(PTRACE_SINGLESTEP, ftrace->strace.pid, NULL, 0) == -1) {
            perror("ptrace");
            break;
        }
        safe_waitpid(ftrace->strace.pid, &stat_loc, 0);
    }
}

static void clean_map(mem_map_t ***map)
{
    if (!map || !*map) {
        return;
    }
    for (size_t i = 0; (*map)[i]; ++i) {
        safe_free((Object_t **) &(*map)[i]->perm);
        safe_free((Object_t **) &(*map)[i]->source_file);
        safe_free((Object_t **) &(*map)[i]);
    }
    free(*map);
    *map = NULL;
}

void strace_start_tracing(ftrace_t *ftrace)
{
    int stat_loc = 0;
    mem_map_t __attribute__((cleanup(clean_map)))**map = NULL;

    safe_waitpid(ftrace->strace.pid, &stat_loc, 0);
    if (ptrace(
        PTRACE_SETOPTIONS, ftrace->strace.pid, NULL, PTRACE_O_TRACEEXIT) == -1)
        perror("ptrace");
    map = load_process_maps(ftrace->strace.pid);
    loop(stat_loc, ftrace, map);
}
