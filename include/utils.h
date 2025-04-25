/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** Utils.h
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include <stdio.h>
    #include <stdbool.h>
    #include <sys/stat.h>

void raise_error(const char *where, const char *why);

// static inline bool is_executable(const char *path)
// {
//     struct stat st;

//     return stat(path, &st) == 0 && (st.st_mode & S_IXUSR);
// }


#endif /* UTILS_H_ */
