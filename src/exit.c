/*
** EPITECH PROJECT, 2024
** 42sh-private
** File description:
** exit
*/

#include "../include/mysh.h"

int my_exit(char **command_array, shell_t *shell)
{
    if (my_strlen_array(command_array) == 1) {
        shell->last_return = 0;
        shell->exit = 1;
        return 1;
    } else {
        if (my_strlen_array(command_array) != 2 || command_array[1][0] < '0' ||
        command_array[1][0] > '9') {
            mini_fdprintf(shell->pipefd[1], "exit: Expression Syntax.\n");
            shell->last_return = 1;
            return 1;
        }
        if (!my_str_isnum(command_array[1])) {
            mini_fdprintf(shell->pipefd[1], "exit: Badly formed number.\n");
            shell->last_return = 1;
            return 1;
        }
    }
    shell->last_return = convert_str_in_int(command_array[1]);
    shell->exit = 1;
    return 1;
}
