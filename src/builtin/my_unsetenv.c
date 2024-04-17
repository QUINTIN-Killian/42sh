/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** delete an environment variable
** my_unsetenv
*/

#include "../../include/mysh.h"

int my_unsetenv(char **command_array, shell_t *shell)
{
    if (my_strlen_array(command_array) == 1) {
        shell->last_return = 1;
        return 1;
    }
    for (int i = 1; i < my_strlen_array(command_array); i++)
        del_env(shell, command_array[i]);
    shell->last_return = 0;
    return 1;
}
