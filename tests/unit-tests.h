/*
** EPITECH PROJECT, 2025
** PSU-ftrace
** File description:
** unit-tests.h
*/

#ifndef FTRACE_UNIT_TESTS_H_
    #define FTRACE_UNIT_TESTS_H_

    #include <criterion/criterion.h>
    #include <criterion/logging.h>

bool is_number(const char *str);
void raise_error(const char *restrict format, ...);
char **my_str_to_word_array(char const *str, char *separator);
bool get_elf_architecture(const unsigned char *restrict buffer,
    const size_t size, const char *restrict filename);


#endif /* !FTRACE_UNIT_TESTS_H_ */
