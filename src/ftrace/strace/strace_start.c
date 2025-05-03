/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_start.c
*/

#include "interface.h"
#include "parse.h"
#include "strace.h"
#include "shared_lib.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "macro.h"

/**
 * @brief check if the instruction at RIP is a CALL instruction
 * @details skip any REX prefix (0x40 - 0x4F)
 *
 *          read the first 2 bytes at RIP using ptrace
 *
 *          0xE8 => direct      (call rel32)
 *          0xFF/2 => indirect  (call r/m64)
 *
 * @bitshift
 *   0xFF               => 1111
 *   modrm >> 3 & 0x07  => the bits 3-5 determine the instruction
 *
 *   \example:
 *     - 0xFF / 0 -> INC r/m64
 *     - 0xFF / 1 -> DEC r/m64
 *     - 0xFF / 2 -> CALL r/m64
 *     ...
 *
 * @return 1 if it's a call instruction, 0 otherwise.
 */
static _Bool is_call_instruction(pid_t pid, size_t rip)
{
    long data = ptrace(PTRACE_PEEKTEXT, pid, (void *)rip, NULL);
    uint8_t *bytes = NULL;
    size_t idx = 0;
    uint8_t modrm = 0;
    uint8_t reg = 0;

    if (data == ERR)
        return FAILED;
    bytes = (uint8_t *)&data;
    if ((bytes[0] & 0xF0) == 0x40)
        idx = 1;
    if (bytes[idx] == 0xE8)
        return DIRECT_CALL;
    if (bytes[idx] == 0xFF) {
        modrm = bytes[idx + 1];
        reg = (modrm >> 3) & 0x07;
        if (reg == 2)
            return INDIRECT_CALL;
    }
    return FAILED;
}

/**
* @brief strace execvp program
* @details try to execvp the given program & try to trace it
*  | otherse raise an error
*/
void strace_execvp_prog(strace_t *strace)
{
    if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == ERR) {
        raise_error("strace_execvp_prog", "ptrace failed");
    }
    if (execvp(strace->prog, (char **)&strace->prog) == ERR) {
        raise_error("strace_execvp_prog", "execvp failed");
    }
}

static bool fetch_registers(pid_t pid, struct user_regs_struct *regs)
{
    if (ptrace(PTRACE_GETREGS, pid, NULL, regs) == ERR) {
        perror("ptrace");
        return false;
    }
    return true;
}

static bool try_function_return(ftrace_t *ftrace, size_t prev_sp)
{
    if (ftrace->strace.regs.rsp > prev_sp) {
        check_for_returns(ftrace, ftrace->strace.regs.rsp);
    }
    return true;
}

static bool try_function_call(ftrace_t *ftrace, mem_map_t **m, int *stat_loc)
{
    if (!is_call_instruction(ftrace->strace.pid, ftrace->strace.regs.rip))
        return true;
    if (ptrace(PTRACE_SINGLESTEP, ftrace->strace.pid, NULL, 0) == ERR) {
        perror("ptrace");
        return false;
    }
    safe_waitpid(ftrace->strace.pid, stat_loc, 0);
    if (WIFEXITED(*stat_loc)) {
        return false;
    }
    if (!fetch_registers(ftrace->strace.pid, &ftrace->strace.regs))
        return false;
    get_func_call(ftrace->strace.regs.rip, m, ftrace, ftrace->strace.regs.rsp);
    return true;
}

static bool check_function_call_or_return(ftrace_t *ftrace, mem_map_t **map,
    int *stat_loc, size_t prev_sp)
{
    static bool is_first_call = true;

    if (!is_first_call) {
        if (!try_function_return(ftrace, prev_sp)) {
            return true;
        }
        if (!try_function_call(ftrace, map, stat_loc)) {
            return true;
        }
    }
    is_first_call = false;
    return false;
}

void loop(int stat_loc, ftrace_t *ftrace, mem_map_t **map)
{
    size_t prev_sp = 0;

    while (!WIFEXITED(stat_loc)) {
        if (!fetch_registers(ftrace->strace.pid, &ftrace->strace.regs))
            break;
        if (check_function_call_or_return(ftrace, map, &stat_loc, prev_sp))
            break;
        prev_sp = ftrace->strace.regs.rsp;
        strace_display_trace(&ftrace->strace);
        if (ptrace(PTRACE_SINGLESTEP, ftrace->strace.pid, NULL, 0) == ERR) {
            perror("ptrace");
            break;
        }
        safe_waitpid(ftrace->strace.pid, &stat_loc, 0);
    }
    clean_stack(&ftrace);
}

void strace_start_tracing(ftrace_t *ftrace)
{
    int stat_loc = 0;
    mem_map_t __attribute__((cleanup(clean_map)))**map = NULL;

    safe_waitpid(ftrace->strace.pid, &stat_loc, 0);
    if (ptrace(
        PTRACE_SETOPTIONS,
        ftrace->strace.pid, NULL, PTRACE_O_TRACEEXIT) == ERR) {
        perror("ptrace");
        return;
    }
    map = load_process_maps(ftrace->strace.pid);
    loop(stat_loc, ftrace, map);
}
