/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** scanf function
** my_scanf
*/

#include "../include/mysh.h"

char *my_scanf(void)
{
    char *lineptr = NULL;
    char *ans = NULL;
    size_t n = 0;

    if (getline(&lineptr, &n, stdin) == -1) {
        free(lineptr);
        return NULL;
    }
    if (my_strlen(lineptr) != 1) {
        ans = my_strndup(lineptr, my_strlen(lineptr) - 1);
        free(lineptr);
        return ans;
    }
    return lineptr;
}
