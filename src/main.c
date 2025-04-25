/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** main.c
*/

#include "macro.h"
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

static int usage(void)
{
    printf("USAGE: ftrace <command>\n");
    return SUCCESS;
}

static bool is_executable_extension(const char *restrict filename)
{
    const char *restrict ext = strrchr(filename, '.');

    if (ext && (strcmp(ext, ".so") == 0 || strcmp(ext, ".a") == 0)) {
        return true;
    }
    return false;
}

static bool is_executable(const char *restrict filename)
{
    struct stat st;

    if (stat(filename, &st) != 0) {
        return false;
    }
    if (!S_ISREG(st.st_mode)) {
        return false;
    }
    if (access(filename, X_OK) == 0) {
        return true;
    }
    return is_executable_extension(filename);
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
    return SUCCESS;
}

int main(int argc, char **argv)
{
    return parse_arguments(argc, argv);
}
