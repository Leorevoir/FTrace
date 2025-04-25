/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** init_ftrace.c
*/

#include "parse.h"
#include "shared_lib.h"
#include "ftrace.h"
#include <stdio.h>

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

static void ftrace_ctor(ftrace_t *ftrace, const char *restrict filename)
{
    get_file_content(filename, &ftrace->file);
}

static void ftrace_dtor(ftrace_t *ftrace)
{
    safe_free((Object_t **)&ftrace->file.buffer);
}

void init_ftrace(const char *restrict filename)
{
    ftrace_t ftrace = {0};

    ftrace_ctor(&ftrace, filename);
    if (get_elf_architecture(ftrace.file.buffer, ftrace.file.size, filename)) {
        get_nm_elf_64(&ftrace.nm, ftrace.file);
    } else {
        get_nm_elf_32(&ftrace.nm, ftrace.file);
    }
    ftrace_dtor(&ftrace);
}
