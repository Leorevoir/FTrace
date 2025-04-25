/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** main.c
*/

#include "macro.h"
#include "parse.h"
#include <stdio.h>
#include "ftrace.h"

static int usage(void)
{
    printf("USAGE: ftrace <executable | .so | .a>\n");
    return SUCCESS;
}

int parse_arguments(int argc, char **argv, char **env)
{
    strace_t strace = {0};
    if (argc != 2) {
        return ERROR;
    }
    if (strcmp(argv[1], "-help") == 0) {
        return usage();
    }
    if (!is_executable(argv[1])) {
        return ERROR;
    }
    strace.flag.s = true;
    strace.prog = argv[1];
    strace_init(&strace, env);
    return SUCCESS;
}

int main(int argc, char **argv, char **env)
{
    return parse_arguments(argc, argv, env);
}
