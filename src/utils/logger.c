/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** logger.c
*/

#include "macro.h"
#include <stdarg.h>
#include <stdlib.h>
#include "shared_lib.h"

void raise_error(const char *restrict format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    fflush(stderr);
    exit(ERROR);
}
