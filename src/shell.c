/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** shell management
** shell
*/

#include "../include/mysh.h"

static int print_fd(shell_t *shell)
{
    char buf;

    if (my_strlen_array(shell->separators) == 0 || my_strcmp(shell->separators
    [my_strlen_array(shell->separators) - 1], "|") == 0) {
        while (read(shell->fd_input, &buf, 1) > 0) {
            write(1, &buf, 1);
        }
        close(shell->pipefd[0]);
    }
    return 1;
}

static int parse_multiple_commands_aux(shell_t *shell)
{
    shell->fd_input = -1;
    shell->ind = -1;
    for (int i = 0; i < my_strlen_array(shell->command_array_sep); i++) {
        shell->command_array =
        sep_str(shell->command_array_sep[i], 2, "\t", " ");
        if (explore_var_env(shell)) {
            free_word_array(shell->command_array);
            return 0;
        }
        pipe(shell->pipefd);
        command_interpreter(shell, i);
        if (shell->fd_input != -1)
            close(shell->fd_input);
        shell->fd_input = shell->pipefd[0];
        close(shell->pipefd[1]);
        free_word_array(shell->command_array);
    }
    return print_fd(shell);
}

static void parse_multiple_commands(shell_t *shell)
{
    char **multiple_commands = sep_str(shell->input, 1, ";");

    for (int i = 0; i < my_strlen_array(multiple_commands); i++) {
        shell->separators = NULL;
        get_command_separators(shell, multiple_commands[i]);
        shell->command_array_sep = sep_str(multiple_commands[i], 5,
        "|", "<", ">", "<<", ">>");
        if (shell->command_array_sep == NULL)
            continue;
        if (!parse_multiple_commands_aux(shell))
            i = my_strlen_array(multiple_commands);
        free_word_array(shell->separators);
        free_word_array(shell->command_array_sep);
    }
    free_word_array(multiple_commands);
}

int shell_interface(shell_t *shell)
{
    while (!shell->exit) {
        if (isatty(0))
            mini_printf("$> ");
        shell->input = my_scanf();
        if (shell->input == NULL)
            return 1;
        if ((my_strlen(shell->input) == 1 && shell->input[0] == '\n') ||
        error_handling_input(shell)) {
            free(shell->input);
            continue;
        }
        parse_multiple_commands(shell);
        free(shell->input);
    }
    return 0;
}
