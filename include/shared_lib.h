/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** shared_lib.h
*/

#ifndef FTRACE_SHARED_H_
    #define FTRACE_SHARED_H_

    #include "sys/types.h"
    #include <stdio.h>

/**
 * @brief raise_error
 * @details write the error msg and exit the program with ERROR code
 */
void raise_error(const char *__restrict format, ...);

/**
 * @brief safe lib
 * @details safer memory-access methods
 */

typedef void Object_t;

void safe_fclose(FILE **stream_ptr);
void safe_free(Object_t **ptr);

void safe_alloc(Object_t **ptr, const size_t size);
void safe_fopen(const char *__restrict filename, FILE **stream_ptr);

void safe_waitpid(pid_t pid, int *stat_loc, int options);
void safe_fork(pid_t *pid);

static inline void safe_free_char(char **ptr)
{
    safe_free((Object_t **)ptr);
}

#endif /* FTRACE_SHARED_H_ */
