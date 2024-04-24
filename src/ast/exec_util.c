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

int is_builtin_exp(char **args, shell_t *shell)
{
    if (my_strcmp(args[0], "exit") == 0)
        return my_exit(args, shell);
    if (my_strcmp(args[0], "cd") == 0)
        return my_cd(args, shell);
    return 0;
}
