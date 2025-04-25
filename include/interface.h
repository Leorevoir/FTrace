/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** interface.h
*/

#ifndef FTRACE_INTERFACE_H_
    #define FTRACE_INTERFACE_H_

    #include <stddef.h>
    #include <elf.h>
    #include <stdbool.h>

typedef struct symbol_s {
    const Elf64_Sym *sym;
    Elf64_Addr value;
    const char *__restrict name;
} symbol_t;

typedef struct nm_s {
    symbol_t *symbols;
    size_t symbol_count;
} nm_t;

typedef struct file_s {
    unsigned char *buffer;
    size_t size;
} file_t;

typedef struct ftrace_s {
    file_t file;
    nm_t nm;
} ftrace_t;

#endif /* FTRACE_INTERFACE_H_ */
