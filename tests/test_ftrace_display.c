/*
** EPITECH PROJECT, 2025
** STRACE
** File description:
** test display
*/

#include "ftrace_syscall.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/stat.h>
#include <unistd.h>

Test(register_to_string, test_register_to_string)
{
    pid_t pid = getpid();
    size_t reg = 0;
    char *result = register_to_string(pid, reg);

    cr_assert_null(result);
    free(result);
}

Test(register_to_void, test_register_to_void)
{
    pid_t pid = getpid();
    size_t reg = 0;
    char *result = register_to_void(pid, reg);

    cr_assert_str_eq(result, "");
}

Test(register_to_pvoid, test_register_to_pvoid)
{
    pid_t pid = getpid();
    size_t reg = 0;
    char *result = register_to_pvoid(pid, reg);

    cr_assert_str_eq(result, "NULL");
}

Test(register_to_addr, test_register_to_addr)
{
    size_t reg = 0x12345678;
    char *result = register_to_addr(0, reg);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "0x12345678");
    free(result);
    reg = 0;
    result = register_to_addr(0, reg);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "0x0");
    free(result);
    reg = 0xFFFFFFFFFFFFFFFF;
    result = register_to_addr(0, reg);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "0xffffffffffffffff");
    free(result);
    reg = 0x1;
    result = register_to_addr(0, reg);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "0x1");
    free(result);
}

Test(register_to_unigned, test_register_to_unigned)
{
    pid_t pid = getpid();
    size_t reg = 69;
    char *result = register_to_unsigned(pid, reg);

    cr_assert_str_eq(result, "69");
}

Test(register_to_signed, test_register_to_signed)
{
    pid_t pid = getpid();
    size_t reg = 1;
    char *result = register_to_signed(pid, reg);

    cr_assert_str_eq(result, "1");
}

Test(register_to_string, test_register_to_string_hard)
{
    pid_t pid = getpid();
    size_t reg = 0x1000;
    char *result = register_to_string(pid, reg);

    cr_assert_null(result);
    free(result);
    reg = 0;
    result = register_to_string(pid, reg);
    cr_assert_null(result);
}
