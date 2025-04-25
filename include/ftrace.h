/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** ftrace.h
*/

#ifndef FTRACE_H_H
    #define FTRACE_H_H

    #include "interface.h"

void init_ftrace(const char *__restrict filename);

void get_nm_elf_64(nm_t *nm, const file_t file);
void get_nm_elf_32(nm_t *nm, const file_t file);

#endif /* FTRACE_H_H */
