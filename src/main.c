/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** main.c
*/

#include "macro.h"
#include "parse.h"
#include "ftrace.h"
#include <stdio.h>

static int usage(void)
{
    printf("USAGE: ftrace <executable | .so | .a>\n");
    return SUCCESS;
}

static flag_t get_flags(int argc, char **argv)
{
    flag_t flags = {0};

    if (argc != 3) {
        return flags;
    }
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-s") == 0) {
            flags.s = true;
        }
    }
    return flags;
}

int parse_arguments(int argc, char **argv, char **env)
{
    if (argc != 2 && argc != 3) {
        return ERROR;
    }
    if (strcmp(argv[1], "-help") == 0) {
        return usage();
    }
    if (!is_executable(argv[1])) {
        return ERROR;
    }
    init_ftrace(argv[1], env, get_flags(argc, argv));
    return SUCCESS;
}

int main(int argc, char **argv, char **env)
{
    return parse_arguments(argc, argv, env);
}
