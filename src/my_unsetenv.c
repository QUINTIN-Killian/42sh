/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** delete an environment variable
** my_unsetenv
*/

#include "../include/mysh.h"

int my_unsetenv(shell_t *shell)
{
    if (my_strlen_array(shell->command_array) == 1) {
        shell->last_return = 1;
        return 1;
    }
    for (int i = 1; i < my_strlen_array(shell->command_array); i++)
        del_env(shell, shell->command_array[i]);
    shell->last_return = 0;
    return 0;
}
