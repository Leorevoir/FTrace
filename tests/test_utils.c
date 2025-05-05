/*
** EPITECH PROJECT, 2025
** PSU-ftrace
** File description:
** test-utils
*/

#include "shared_lib.h"
#include "unit-tests.h"
#include <stdlib.h>
#include <sys/wait.h>

Test(is_number, test_is_number)
{
    cr_assert_eq(is_number("123"), true);
}

Test(is_number, test_is_not_number)
{
    cr_assert_eq(is_number("sad"), false);
}

Test(raise_error, exits_with_84)
{
    pid_t pid = 0;
    int status = 0;

    safe_fork(&pid);
    cr_assert_neq(pid, -1, "fork failed");
    if (pid == 0) {
        raise_error("failed!");
        exit(0);
    }
    safe_waitpid(pid, &status, 0);
    cr_assert(WIFEXITED(status), "Child did not exit normally");
    cr_assert_eq(WEXITSTATUS(status), 84, "raise_error did not exit with 84");
}

Test(my_str_to_word_array, test_my_str_to_word_array)
{
    char **result = my_str_to_word_array("hello world", " ");

    cr_assert_str_eq(result[0], "hello");
    cr_assert_str_eq(result[1], "world");
    cr_assert_null(result[2]);
    free(result[0]);
    free(result[1]);
    free(result);
}
