/*
** EPITECH PROJECT, 2025
** FTRACE
** File description:
** test_ftrace.c
*/

#include "ftrace.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_output(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(init_ftrace, test_init_ftrace64, .init=redirect_all_output)
{
    char *env[] = {"PATH=/usr/bin", NULL};
    const char *filename = "tests/elf_bin64";
    flag_t flag = {0};

    init_ftrace(filename, env, flag);
}
