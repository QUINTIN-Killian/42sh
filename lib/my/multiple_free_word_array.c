/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** free multiple word array pointers
** multiple_free_word_array
*/

#include "my.h"

void multiple_free_word_array(int nb_free, ...)
{
    va_list args;
    char **word_array;

    va_start(args, nb_free);
    for (int i = 0; i < nb_free; i++) {
        word_array = va_arg(args, char **);
        if (word_array != NULL) {
            free_word_array(word_array);
        }
    }
    va_end(args);
}
