/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** exit management
** exit
*/

#include "../include/mysh.h"

int error_handling_exit(shell_t *shell)
{
    if (my_strlen_array(shell->command_array) == 1) {
        shell->last_return = 0;
        shell->exit = 1;
        return 0;
    } else {
        if (my_strlen_array(shell->command_array) != 2 ||
        shell->command_array[1][0] < '0' || shell->command_array[1][0] > '9') {
            mini_fdprintf(shell->pipefd[1], "exit: Expression Syntax.\n");
            shell->last_return = 1;
            return 0;
        }
        if (!my_str_isnum(shell->command_array[1])) {
            mini_fdprintf(shell->pipefd[1], "exit: Badly formed number.\n");
            shell->last_return = 1;
            return 0;
        }
    }
    shell->last_return = convert_str_in_int(shell->command_array[1]);
    shell->exit = 1;
    return 0;
}
