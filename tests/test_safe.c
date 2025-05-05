/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** test_safe.c
*/

#include <criterion/criterion.h>
#include <signal.h>
#include "shared_lib.h"

Test(safe_fclose, test_safe_fclose)
{
    FILE *file = NULL;

    file = fopen("Makefile", "rb");
    cr_assert_not_null(file);
    safe_fclose(&file);
    cr_assert_null(file);
}

Test(safe_fopen, test_safe_fopen)
{
    FILE *file = NULL;

    safe_fopen("Makefile", &file);
    cr_assert_not_null(file);
    safe_fclose(&file);
    cr_assert_null(file);
}

Test(safe_alloc, test_safe_alloc)
{
    Object_t *obj = NULL;

    safe_alloc(&obj, sizeof(Object_t *));
    cr_assert_not_null(obj);
    safe_free((Object_t **)&obj);
    cr_assert_null(obj);
}

Test(safe_free, test_safe_free)
{
    Object_t *obj = malloc(sizeof(Object_t *));

    cr_assert_not_null(obj);
    safe_free(&obj);
    cr_assert_null(obj);
}

Test(safe_fork, test_safe_fork)
{
    pid_t pid = 0;

    safe_fork(&pid);
    cr_assert_gt(pid, 0);
    kill(pid, SIGKILL);
}

Test(safe_waitpid, test_safe_waitpid)
{
    pid_t pid = 0;
    int status = 0;

    safe_fork(&pid);
    cr_assert_gt(pid, 0);
    kill(pid, SIGKILL);
    safe_waitpid(pid, &status, 0);
    cr_assert_eq(WIFSIGNALED(status), 1);
}

Test(safe_free_char, test_safe_free_char)
{
    char *str = malloc(sizeof(char) * 10);

    cr_assert_not_null(str);
    safe_free_char(&str);
    cr_assert_null(str);
}
