/*
** EPITECH PROJECT, 2023
** c_pool day08
** File description:
** my_str_to_word_array: put all the words in an array.
*/

#include "parse.h"
#include <stdlib.h>

void ar_putchars(char const *str, int length,
    int starting_point, char *array_str)
{
    int char_count = 0;

    for (int i = starting_point; i < starting_point + length; i++) {
        array_str[char_count] = str[i];
        char_count++;
    }
    array_str[char_count] = '\0';
}

int char_is_alpha(char chr, char *separator)
{
    for (int i = 0; separator[i] != '\0'; i++) {
        if (chr != '\0' && chr != separator[i])
            continue;
        return 0;
    }
    return 1;
}

void allocate_chars(char **tab, int word_number,
    char const *str, char *separator)
{
    int char_nb = 0;
    int word_nb = 0;

    for (int i = 0; str[i] != '\0' && word_nb <= word_number; i++) {
        if (char_is_alpha(str[i], separator) == 1 &&
            char_is_alpha(str[i + 1], separator) == 0) {
            char_nb++;
            tab[word_nb] = malloc(sizeof(char) * (long unsigned)(char_nb + 1));
            ar_putchars(str, char_nb, i - char_nb + 1, tab[word_nb]);
            char_nb = 0;
            word_nb++;
            continue;
        }
        if (char_is_alpha(str[i], separator) == 1) {
            char_nb++;
        }
    }
}

char **my_str_to_word_array(char const *str, char *separator)
{
    int count_words = 0;
    char **my_word_array;

    for (int i = 1; str[i] != '\0'; i++) {
        if (i == 1 && char_is_alpha(str[0], separator) == 1) {
            count_words++;
            continue;
        }
        if (char_is_alpha(str[i], separator) == 1 &&
            char_is_alpha(str[i - 1], separator) == 0)
            count_words++;
    }
    my_word_array = malloc(sizeof(char *) * (long unsigned)(count_words + 1));
    my_word_array[count_words] = 0;
    allocate_chars(my_word_array, count_words, str, separator);
    return my_word_array;
}
