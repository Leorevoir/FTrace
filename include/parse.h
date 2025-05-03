/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** parse.h
*/

#ifndef FTRACE_PARSE_H_
    #define FTRACE_PARSE_H_

    #include <stdbool.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include "interface.h"

static inline _Bool is_executable_extension(const char *__restrict filename)
{
    const char *restrict ext = strrchr(filename, '.');

    if (ext && (strcmp(ext, ".so") == 0 || strcmp(ext, ".a") == 0)) {
        return true;
    }
    return false;
}

static inline _Bool is_executable(const char *__restrict filename)
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

bool get_elf_architecture(
    const unsigned char *restrict buffer,
    const size_t size, const char *restrict filename);
char **my_str_to_word_array(char const *str, char *separator);
mem_map_t **load_process_maps(pid_t pid);

#endif /* FTRACE_PARSE_H_ */
