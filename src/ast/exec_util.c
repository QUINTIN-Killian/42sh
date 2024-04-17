/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** exec_util.c
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../../include/mysh.h"

int print_execve_error(char *command, char *error)
{
    mini_fdprintf(2, "%s: %s", command, error);
    return BUILTIN_ERROR;
}
