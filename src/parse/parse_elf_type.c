/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** parse_elf_type.c
*/

#include "shared_lib.h"
#include <elf.h>
#include <stdbool.h>
#include <string.h>

static void is_valid_elf32(const unsigned char *restrict buffer,
    const size_t size, const char *restrict filename)
{
    const Elf64_Ehdr *ehdr = (Elf64_Ehdr *)buffer;

    if (ehdr->e_shoff > size || ehdr->e_shoff + (
        ehdr->e_shnum * sizeof(Elf64_Ehdr)) > size) {
        raise_error("ftrace: %s: file format not recognized", filename);
    }
    if (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN
        && ehdr->e_type != ET_REL) {
        raise_error("ftrace: %s: unsupported file type", filename);
    }
}

static void is_valid_elf64(const unsigned char *restrict buffer,
    const size_t size, const char *restrict filename)
{
    const Elf32_Ehdr *ehdr = (Elf32_Ehdr *)buffer;

    if (ehdr->e_shoff > size || ehdr->e_shoff + (
        ehdr->e_shnum * sizeof(Elf32_Ehdr)) > size) {
        raise_error("ftrace: %s: file format not recognized", filename);
    }
    if (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN
        && ehdr->e_type != ET_REL) {
        raise_error("ftrace: %s: unsupported file type", filename);
    }
}

static bool is_valid_elf(const unsigned char *restrict e_ident)
{
    return !memcmp(e_ident, ELFMAG, SELFMAG);
}

bool get_elf_architecture(const unsigned char *restrict buffer,
    const size_t size, const char *restrict filename)
{
    const unsigned char *e_ident = buffer;
    const bool is_64 = (e_ident[EI_CLASS] == ELFCLASS64);

    if (!is_valid_elf(e_ident)) {
        raise_error("ftrace: %s: file format not recognized", filename);
    }
    if (is_64) {
        is_valid_elf64(buffer, size, filename);
        return is_64;
    }
    is_valid_elf32(buffer, size, filename);
    return is_64;
}
