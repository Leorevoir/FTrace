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
    #include <sys/types.h>
    #include <sys/user.h>

typedef struct symbol_s {
    const Elf64_Sym *sym;
    Elf64_Addr value;
    const char *__restrict name;
} symbol_t;

typedef struct nm_s {
    symbol_t *symbols;
    size_t symbol_count;
} nm_t;

typedef struct flag_s {
    bool p;
    pid_t pid;
    bool s;
} flag_t;

typedef struct strace_s {
    pid_t pid;
    char **env;
    flag_t flag;
    const char *prog;
    struct user_regs_struct regs;
    size_t env_count;
} strace_t;

typedef struct file_s {
    unsigned char *buffer;
    size_t size;
} file_t;

typedef struct ftrace_s {
    file_t file;
    nm_t nm;
    strace_t strace;
} ftrace_t;

typedef struct mem_map_s {
    unsigned long region[2];
    char *perm;
    unsigned long offset;
    char *source_file;
} mem_map_t;

#endif /* FTRACE_INTERFACE_H_ */
