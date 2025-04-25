/*
** EPITECH PROJECT, 2025
** Ftrace
** File description:
** safe_memory.c
*/

#include "shared_lib.h"
#include <stdlib.h>

void safe_fclose(FILE **ptr)
{
    if (!ptr || !*ptr) {
        return;
    }
    fclose(*ptr);
    *ptr = NULL;
}

void safe_free(Object_t **ptr)
{
    if (!ptr || !*ptr) {
        return;
    }
    free(*ptr);
    *ptr = NULL;
}

void safe_alloc(Object_t **ptr, const size_t size)
{
    *ptr = malloc(size);
    if (!*ptr) {
        raise_error("safe_alloc: malloc failed! no more memory!");
    }
}

void safe_fopen(const char *restrict filename, FILE **stream_ptr)
{
    *stream_ptr = fopen(filename, "rb");
    if (*stream_ptr == NULL) {
        raise_error("ftrace: get_file_content failed to open %s", filename);
    }
}
