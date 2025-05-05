/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** test_aprse_elf_type.c
*/

#include <elf.h>
#include "unit-tests.h"
#include <stdio.h>

Test(get_elf_architecture, test_get_elf_architecture64)
{
    FILE *file = fopen("tests/elf_bin64", "rb");
    unsigned char buffer[sizeof(Elf64_Ehdr)];
    size_t size = fread(buffer, 1, sizeof(buffer), file);

    bool result = get_elf_architecture(buffer, size, "tests/elf_bin64");
    cr_assert_eq(result, true);
    fclose(file);
}
