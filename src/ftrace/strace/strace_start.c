/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_start.c
*/

/**
 * TODO: creer une struct pour stocker la map (pas tout mais uniquement les ranges pour calculer l'offset)
 * TODO: envoyer nm_t pour pouvoir recup les noms de fonctions
 * TODO: gerer les autres types de call (pas que 0xE8)
 */

#include "strace.h"
#include "parse.h"
#include "shared_lib.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static unsigned long get_call_target(pid_t pid, unsigned long rip, unsigned char *instruction)
{
    if (instruction[0] == 0xE8) {
        long data = ptrace(PTRACE_PEEKDATA, pid, rip + 1, NULL);
        long unsigned offset = data & 0xFFFFFFFF; // Extract 32-bit offset
        
        return rip + 5 + offset;
    }
    return 0;
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

void strace_start_tracing(ftrace_t *ftrace)
{
    int stat_loc = 0;
    unsigned char instruction[16];
    unsigned long rip;
    safe_waitpid(ftrace->strace.pid, &stat_loc, 0);
    mem_map_t **map = load_process_maps(ftrace->strace.pid);
    unsigned long target = 0;

    if (ptrace(PTRACE_SETOPTIONS, ftrace->strace.pid, NULL, PTRACE_O_TRACEEXIT) == -1) {
        perror("ptrace");
    }
    while (!WIFEXITED(stat_loc)) {
        if (ptrace(PTRACE_GETREGS, ftrace->strace.pid, NULL, &ftrace->strace.regs) == -1) {
            perror("ptrace");
            break;
        }
        rip = ftrace->strace.regs.rip;
        long instr_data = ptrace(PTRACE_PEEKDATA, ftrace->strace.pid, rip, NULL);
        memcpy(instruction, &instr_data, sizeof(long));
        if (instruction[0] == 0xE8) {
            target = get_call_target(ftrace->strace.pid, rip, instruction);
            printf("call instruction: 0x%lx\n", target);
        }
        for (int i = 0; map[i]; ++i) {
            if (target > map[i]->region[0] && target < map[i]->region[1]) {
                printf("==================FOUND ONE====================\n");
                printf("-> %lx\n", target - map[i]->region[0]);
                for (size_t j = 0; j < ftrace->nm.symbol_count; ++j) {
                    if (ftrace->nm.symbols &&  target - map[i]->region[0] == ftrace->nm.symbols[j].value) {
                        printf("ON A TROUVE %s\n", ftrace->nm.symbols[j].name);
                        break;
                    }
                }
            }
        }
        strace_display_trace(&ftrace->strace);


        if (ptrace(PTRACE_SINGLESTEP, ftrace->strace.pid, NULL, 0) == -1) {
            perror("ptrace");
            break;
        }

        safe_waitpid(ftrace->strace.pid, &stat_loc, 0);
    }
}
