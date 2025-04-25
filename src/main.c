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

int parse_arguments(int argc, char **argv)
{
    if (argc != 2) {
        return ERROR;
    }
    if (strcmp(argv[1], "-help") == 0) {
        return usage();
    }
    if (!is_executable(argv[1])) {
        return ERROR;
    }
    init_ftrace(argv[1]);
    return SUCCESS;
}

int main(int argc, char **argv)
{
    return parse_arguments(argc, argv);
}
