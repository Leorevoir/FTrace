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
    const Elf64_Addr value;
    const char *__restrict name;
    const char type;
} symbol_t;

typedef struct nm_s {
    struct {
        unsigned char *buffer;
        size_t size;
    } file;
    bool is_64;
    symbol_t *symbols;
    size_t symbol_count;
} nm_t;

#endif /* FTRACE_INTERFACE_H_ */
