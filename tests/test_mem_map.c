/*
** EPITECH PROJECT, 2025
** FTRACE
** File description:
** test_mem_map.c
*/

#include "unit-tests.h"
#include "interface.h"
#include <limits.h>
#include "shared_lib.h"
#include <unistd.h>

mem_map_t **load_process_maps(pid_t pid);
void clean_map(mem_map_t ***map);

Test(load_process_maps, test_load_process_map)
{
    mem_map_t **map = load_process_maps(getpid());
    char *path = "/proc/self/maps";
    FILE *stream = NULL;
    char line[MAX_INPUT] = {0};

    cr_assert_not_null(map, "Failed to load process maps");
    cr_assert_not_null(map[0], "Failed to load process maps");
    safe_fopen(path, &stream);
    for (size_t i = 0; fgets(line, sizeof(line), stream); ++i) {
        cr_assert_not_null(map[i], "Failed to load process maps");
    }
    clean_map(&map);
    fclose(stream);
}
