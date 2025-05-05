/*
** EPITECH PROJECT, 2025
** FTRACE
** File description:
** test_elf32.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shared_lib.h"
#include "interface.h"

void get_nm_elf_32(nm_t *nm, const file_t file);

static void redirect_all_output(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static size_t get_stream_size(FILE *stream)
{
    long size = 0;

    fseek(stream, 0, SEEK_END);
    size = ftell(stream);
    rewind(stream);
    return (size_t)size;
}

static void read_stream_buffer(FILE *stream, unsigned char **ptr, size_t *br)
{
    const size_t size = get_stream_size(stream);
    unsigned char *buff = NULL;

    safe_alloc((Object_t **)&buff, size);
    if (!buff) {
        raise_error("ftrace: read_stream_buffer malloc failed");
    }
    *br = fread(buff, 1, size, stream);
    if (*br != size) {
        safe_free((Object_t **)buff);
        raise_error("ftrace: read_stream_buffer: br != size");
    }
    *ptr = buff;
}

static void get_file_content(const char *restrict f, file_t *file)
{
    FILE *__attribute__((cleanup(safe_fclose)))stream = NULL;

    safe_fopen(f, &stream);
    read_stream_buffer(stream, &file->buffer, &file->size);
}

Test(get_nm_elf_32, test_get_nm_elf_32, .init=redirect_all_output)
{
    const char *filename = "tests/elf_bin32";
    file_t file = {0};
    nm_t nm = {0};

    get_file_content(filename, &file);
    get_nm_elf_32(&nm, file);
    cr_assert_not_null(nm.symbols, "Failed to get symbols");
    cr_assert_gt(nm.symbol_count, 0, "No symbols found");
    free(file.buffer);
    free(nm.symbols);
}
