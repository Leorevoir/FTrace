/*
** EPITECH PROJECT, 2025
** PSU-ftrace
** File description:
** strace_run.c
*/

#include <stdbool.h>
#include "macro.h"
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

/**
 * @brief log the signal received by the child process.
 * @details the display is colored in orange
 * @param sig the signal received.
 */
static void log_signal(const int sig)
{
    if (sig != SIGTRAP) {
        fprintf(stderr, "%sReceived signal %s%s\n",
            ORANGE, strsignal(sig), RST);
    }
}

/**
 * @brief handle signals received by the child process.
 * @param stat_loc the status of the child process.
 * @param pid the PID of the child process.
 * @return true if the child process has exited or been killed
 */
bool strace_handle_signals(int *stat_loc, pid_t __attribute__((unused))*pid)
{
    if (WIFEXITED(*stat_loc)) {
        return true;
    }
    if (WIFSIGNALED(*stat_loc)) {
        log_signal(WTERMSIG(*stat_loc));
        return true;
    }
    if (WIFSTOPPED(*stat_loc)) {
        log_signal(WSTOPSIG(*stat_loc));
    }
    return false;
}
