/*
** EPITECH PROJECT, 2024
** mini_shell2
** File description:
** interprete things
** interpreter
*/

#include "../include/mysh.h"

void separator_interpreter2(shell_t *shell, int i)
{
    if (my_strcmp(shell->separators[shell->ind], ">>") == 0) {
        shell->ind++;
        double_right_redirection(shell, i);
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

void separator_interpreter1(shell_t *shell, int i)
{
    if (shell->separators == NULL || shell->ind == -1 ||
    my_strcmp(shell->separators[shell->ind], "|") == 0) {
        shell->ind++;
        call_bin(shell);
        return;
    }
    if (my_strcmp(shell->separators[shell->ind], ">") == 0) {
        shell->ind++;
        simple_right_redirection(shell);
        return;
    }
    separator_interpreter2(shell, i);
}

void command_interpreter(shell_t *shell, int i)
{
    if (my_strcmp(shell->command_array[0], "exit") == 0 &&
    !error_handling_exit(shell))
        return;
    if (my_strcmp(shell->command_array[0], "env") == 0) {
        my_env(shell);
        return;
    }
    if (my_strcmp(shell->command_array[0], "cd") == 0) {
        my_cd(shell);
        return;
    }
    if (my_strcmp(shell->command_array[0], "setenv") == 0) {
        my_setenv(shell);
        return;
    }
    if (my_strcmp(shell->command_array[0], "unsetenv") == 0) {
        my_unsetenv(shell);
        return;
    }
    if (my_strcmp(shell->command_array[0], "history") == 0) {
        history(shell);
        return;
    }
    separator_interpreter1(shell, i);
}
