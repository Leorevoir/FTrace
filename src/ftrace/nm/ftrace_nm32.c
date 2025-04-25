/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** nm_elf_32.c
*/

#include "interface.h"
#include "shared_lib.h"
#include "ftrace_nm.h"
#include <string.h>
#include <stdlib.h>

static void nm_elf_32_get_valid_symbol(nm_t *nm, const Elf32_Sym *sym32,
    const char *restrict show)
{
    if (strcmp("", show) != 0 && sym32->st_info != STT_FILE) {
        nm->symbols = realloc(nm->symbols, (
            nm->symbol_count + 1) * sizeof(symbol_t));
        nm->symbols[nm->symbol_count] = (symbol_t){
            .sym = (Elf64_Sym *)sym32,
            .name = show,
            .value = sym32->st_value,
        };
        nm->symbol_count++;
    }
}

static void nm_elf_32_get_symtab(nm_t *nm, Elf32_Shdr *shdr, const size_t i,
    const file_t file)
{
    Elf32_Sym *sym32 = (Elf32_Sym *)(file.buffer + shdr[i].sh_offset);
    size_t offset = ELF_OFFSET(shdr, i);
    const size_t size = ELF_SHDR_SIZE(shdr[i]);

    for (size_t unused = 0; unused < size; ++unused) {
        nm_elf_32_get_valid_symbol(nm, sym32, get_sym_name(
            file.buffer, offset, sym32->st_name));
        sym32++;
    }
}

static void nm_elf_32_symtab(nm_t *nm, Elf32_Shdr *shdr, const size_t i,
    const file_t file)
{
    if (shdr[i].sh_type == SHT_SYMTAB) {
        nm_elf_32_get_symtab(nm, shdr, i, file);
    }
}

void get_nm_elf_32(nm_t *nm, const file_t file)
{
    const Elf32_Ehdr *elf = (Elf32_Ehdr *)file.buffer;
    Elf32_Shdr *shdr = (Elf32_Shdr *)(file.buffer + elf->e_shoff);

    nm->symbols = NULL;
    nm->symbol_count = 0;
    for (size_t i = 0; i < elf->e_shnum; ++i) {
        nm_elf_32_symtab(nm, shdr, i, file);
    }
    if (nm->symbol_count == 0) {
        raise_error("ftrace: no symbols");
    }
    safe_free((Object_t **)nm->symbols);
}
