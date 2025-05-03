/*
** EPITECH PROJECT, 2025
** FTRACE
** File description:
** init_mem_map
*/

#include "interface.h"
#include "parse.h"
#include "shared_lib.h"
#include <linux/limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_array(char **array)
{
    for (size_t i = 0; array[i]; ++i) {
        safe_free((Object_t **) &array[i]);
    }
    free(array);
}

static mem_map_t *init_mem_map(char *content)
{
    mem_map_t *map = malloc(sizeof(mem_map_t));
    char **data = NULL;
    char **region_comp = NULL;

    memset(map, 0, sizeof(mem_map_t));
    map->perm = NULL;
    map->source_file = NULL;
    data = my_str_to_word_array(content, " \t");
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
    char path[PATH_MAX] = {0};
    char line[MAX_INPUT] = {0};
    FILE *stream = NULL;
    mem_map_t **map = malloc(sizeof(mem_map_t *));
    size_t size = 1;

    map[0] = NULL;
    snprintf(path, sizeof(path), "/proc/%d/maps", pid);
    safe_fopen(path, &stream);
    for (; fgets(line, sizeof(line), stream); ++size) {
        map = realloc(map, sizeof(mem_map_t *) * (size_t)(size + 1));
        map[size - 1] = init_mem_map(line);
        map[size] = NULL;
    }
    fclose(stream);
    return map;
}
