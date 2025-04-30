/*
** EPITECH PROJECT, 2025
** FTRACE
** File description:
** init_mem_map
*/

#include "interface.h"
#include "parse.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_array(char **array)
{
    for (int i = 0; array[i]; ++i)
        free(array[i]);
    free(array);
}

static mem_map_t *init_mem_map(char *content)
{
    mem_map_t *map = malloc(sizeof(mem_map_t));
    char **data = my_str_to_word_array(content, " \t");
    char **region_comp = NULL;

    if (data)
        region_comp = my_str_to_word_array(data[0], "-");
    map->region[0] = strtoul(region_comp[0], NULL, 16);
    map->region[1] = strtoul(region_comp[1], NULL, 16);
    map->perm = strdup(data[1]);
    map->offset = strtoul(data[2], NULL, 16);
    map->source_file = strdup(data[5]);
    free_array(data);
    free_array(region_comp);
    return map;
}

mem_map_t **load_process_maps(pid_t pid)
{
    char path[64];
    FILE *map_file;
    char line[256];
    mem_map_t **map = malloc(sizeof(mem_map_t));
    int size = 1;

    map[0] = NULL;
    snprintf(path, sizeof(path), "/proc/%d/maps", pid);
    map_file = fopen(path, "r");
    if (!map_file) {
        perror("Failed to open process maps");
        return NULL;
    }
    for (; fgets(line, sizeof(line), map_file); ++size) {
        map = realloc(map, sizeof(mem_map_t) * (long unsigned)(size + 1));
        map[size - 1] = init_mem_map(line);
    }
    map[size] = NULL;
    fclose(map_file);
    return map;
}
