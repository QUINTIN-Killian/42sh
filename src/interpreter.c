/*
** EPITECH PROJECT, 2024
** mini_shell2
** File description:
** interprete things
** interpreter
*/

#include "../include/mysh.h"

void separator_interpreter2(char **command_array, shell_t *shell,
    char **command_array_sep, int i)
{
    if (my_strcmp(shell->separators[shell->ind], ">>") == 0) {
        shell->ind++;
        double_right_redirection(shell, command_array_sep, i, command_array);
        return;
    }
    if (my_strcmp(shell->separators[shell->ind], "<") == 0) {
        shell->ind++;
        my_putstr("<\n");
        return;
    }
    if (my_strcmp(shell->separators[shell->ind], "<<") == 0) {
        shell->ind++;
        my_putstr("<<\n");
        return;
    }
}

void separator_interpreter1(char **command_array, shell_t *shell,
    char **command_array_sep, int i)
{
    if (shell->separators == NULL || shell->ind == -1 ||
    my_strcmp(shell->separators[shell->ind], "|") == 0) {
        shell->ind++;
        call_bin(command_array, shell);
        return;
    }
    if (my_strcmp(shell->separators[shell->ind], ">") == 0) {
        shell->ind++;
        simple_right_redirection(shell, command_array);
        return;
    }
    separator_interpreter2(command_array, shell, command_array_sep, i);
}

void command_interpreter(char **command_array, shell_t *shell,
    char **command_array_sep, int i)
{
    if (my_strcmp(command_array[0], "exit") == 0 &&
    !error_handling_exit(command_array, shell))
        return;
    if (my_strcmp(command_array[0], "env") == 0) {
        my_env(command_array, shell);
        return;
    }
    if (my_strcmp(command_array[0], "cd") == 0) {
        my_cd(command_array, shell);
        return;
    }
    if (my_strcmp(command_array[0], "setenv") == 0) {
        my_setenv(command_array, shell);
        return;
    }
    if (my_strcmp(command_array[0], "unsetenv") == 0) {
        my_unsetenv(command_array, shell);
        return;
    }
    separator_interpreter1(command_array, shell, command_array_sep, i);
}
