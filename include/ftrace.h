/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** ftrace.h
*/

#ifndef FTRACE_H_H
    #define FTRACE_H_H

    #include "interface.h"

void init_ftrace(const char *__restrict filename, char **env,
    flag_t flag);
void init_strace(strace_t *strace, char **env, const char *restrict filename,
    flag_t flag);

void get_nm_elf_64(nm_t *nm, const file_t file);
void get_nm_elf_32(nm_t *nm, const file_t file);

#endif /* FTRACE_H_H */
