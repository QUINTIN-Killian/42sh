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

void my_execve(char *path, char **args, shell_t *shell)
{
    if (execvp(path, args) == -1) {
        mini_fdprintf(2, "%s: %s.", path, strerror(errno));
        if (errno == ENOEXEC)
            mini_fdprintf(2, " Wrong Architecture.");
        mini_fdprintf(2, "\n");
        exit(errno);
    }
}

int print_execve_error(char *command, char *error)
{
    mini_fdprintf(2, "%s: %s", command, error);
    return BUILTIN_ERROR;
}
