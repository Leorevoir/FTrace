/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** parse.h
*/

#ifndef PARSE_H_
    #define PARSE_H_

    #include <stdbool.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <unistd.h>

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

#endif /* PARSE_H_ */
