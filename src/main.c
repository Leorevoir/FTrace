/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** main.c
*/

#include "macro.h"
#include <string.h>
#include <stdio.h>

static int usage(void)
{
    printf("USAGE: ftrace <command>\n");
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
    return ERROR;
}

int main(int argc, char **argv)
{
    return parse_arguments(argc, argv);
}
