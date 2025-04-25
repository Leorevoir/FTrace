/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** ftrace_nm.h
*/

#ifndef FTRACE_NM_H_
    #define FTRACE_NM_H_

    #include <stddef.h>

    #define ELF_OFFSET(x, y) x[x[y].sh_link].sh_offset
    #define ELF_SHDR_SIZE(x) (size_t)(x.sh_size / x.sh_entsize)

static inline const char *get_sym_name(void *buff, const size_t offset,
    const size_t name)
{
    return (const char *)buff + offset + name;
}

#endif /* FTRACE_NM_H_ */
