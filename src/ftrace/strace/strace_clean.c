/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_clean.c
*/

#include "shared_lib.h"
#include "strace.h"
#include <stdlib.h>

void clean_map(mem_map_t ***map)
{
    if (!map || !*map) {
        return;
    }
    for (size_t i = 0; (*map)[i]; ++i) {
        safe_free((Object_t **) &(*map)[i]->perm);
        safe_free((Object_t **) &(*map)[i]->source_file);
        safe_free((Object_t **) &(*map)[i]);
    }
    free(*map);
    *map = NULL;
}

void clean_stack(ftrace_t **ftrace)
{
    call_stack_t *call = NULL;

    if (!ftrace || !*ftrace) {
        return;
    }
    while ((*ftrace)->global_stack != NULL) {
        call = stack_pop_call(ftrace);
        if (call) {
            stack_free_call(&call);
        }
    }
    safe_free((Object_t **) &(*ftrace)->global_stack);
}
