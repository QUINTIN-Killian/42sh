/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** free multiple strings
** multiple_free
*/

#include "my.h"

void multiple_free(int nb_free, ...)
{
    va_list args;
    char *str;

    va_start(args, nb_free);
    for (int i = 0; i < nb_free; i++) {
        str = va_arg(args, char *);
        if (str != NULL) {
            free(str);
        }
    }
    va_end(args);
}
