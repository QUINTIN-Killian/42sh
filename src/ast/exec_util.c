/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** exec_util.c
*/

#include <unistd.h>
#include "../../include/mysh.h"

int print_execve_error(char *command, char *error)
{
    mini_fdprintf(2, "%s: %s", command, error);
    return BUILTIN_ERROR;
}

int is_exit(char **args, shell_t *shell)
{
    if (my_strcmp(args[0], "exit") == 0)
        return my_exit(args, shell);
    return 0;
}
