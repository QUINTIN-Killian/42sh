/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** shell management
** shell
*/

#include "../include/mysh.h"

static bool print_fd(shell_t *shell)
{
    char buf;

    if (my_strlen_array(shell->separators) == 0 || my_strcmp(shell->separators
    [my_strlen_array(shell->separators) - 1], "|") == 0) {
        while (read(shell->fd_input, &buf, 1) > 0) {
            write(1, &buf, 1);
        }
        close(shell->pipefd[0]);
    }
    return true;
}

static char *reimplace_var_env(shell_t *shell, int i)
{
    char *key;

    if (my_strcmp(shell->command_array[i], "$?") == 0) {
        free(shell->command_array[i]);
        shell->command_array[i] = convert_int_to_str(shell->last_return);
        return NULL;
    }
    key = malloc(sizeof(char) * my_strlen(shell->command_array[i]));
    for (int j = 0; j < my_strlen(shell->command_array[i]) - 1; j++)
        key[j] = shell->command_array[i][j + 1];
    key[my_strlen(shell->command_array[i]) - 1] = '\0';
    free(shell->command_array[i]);
    shell->command_array[i] = get_env_value(shell, key);
    if (shell->command_array[i] == NULL)
        return key;
    free(key);
    return NULL;
}

int error_var_env(int i, shell_t *shell)
{
    char *key;

    if (shell->command_array[i][0] == '$') {
        key = reimplace_var_env(shell, i);
        if (key != NULL) {
            mini_printf("%s: Undefined variable.\n", key);
            free(key);
            shell->last_return = 1;
            return 1;
        }
    }
    return 0;
}

int explore_var_env(shell_t *shell)
{
    for (int i = 0; i < my_strlen_array(shell->command_array); i++)
        if (error_var_env(i, shell))
            return 1;
    return 0;
}

static bool parse_multiple_commands_aux(shell_t *shell)
{
    shell->fd_input = -1;
    shell->ind = -1;
    for (int i = 0; i < my_strlen_array(shell->command_array_sep); i++) {
        shell->command_array =
        sep_str(shell->command_array_sep[i], 2, "\t", " ");
        if (explore_var_env(shell)) {
            free_word_array(shell->command_array);
            return false;
        }
        pipe(shell->pipefd);
        command_interpreter(shell, i);
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
