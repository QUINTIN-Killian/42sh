/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** exec_util.c
*/

#include <unistd.h>
#include "../../include/mysh.h"

int print_execve_error(char *command, char *error, char **args)
{
    mini_fdprintf(2, "%s: %s", command, error);
    free_word_array(args);
    return BUILTIN_ERROR;
}
