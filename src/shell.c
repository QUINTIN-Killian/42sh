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

int error_handling_exit(char **command_array, shell_t *shell)
{
    if (my_strlen_array(command_array) == 1) {
        shell->last_return = 0;
        shell->exit = 1;
        return 0;
    } else {
        if (my_strlen_array(command_array) != 2 || command_array[1][0] < '0' ||
        command_array[1][0] > '9') {
            mini_fdprintf(shell->pipefd[1], "exit: Expression Syntax.\n");
            shell->last_return = 1;
            return 0;
        }
        if (!my_str_isnum(command_array[1])) {
            mini_fdprintf(shell->pipefd[1], "exit: Badly formed number.\n");
            shell->last_return = 1;
            return 0;
        }
    }
    shell->last_return = convert_str_in_int(command_array[1]);
    shell->exit = 1;
    return 0;
}

static char *reimplace_var_env(char **command_array, shell_t *shell, int i)
{
    char *key;

    if (my_strcmp(command_array[i], "$?") == 0) {
        free(command_array[i]);
        command_array[i] = convert_int_to_str(shell->last_return);
        return NULL;
    }
    key = malloc(sizeof(char) * my_strlen(command_array[i]));
    for (int j = 0; j < my_strlen(command_array[i]) - 1; j++)
        key[j] = command_array[i][j + 1];
    key[my_strlen(command_array[i]) - 1] = '\0';
    free(command_array[i]);
    command_array[i] = get_env_value(shell, key);
    if (command_array[i] == NULL)
        return key;
    free(key);
    return NULL;
}

int error_var_env(char **command_array, int i, shell_t *shell)
{
    char *key;

    if (command_array[i][0] == '$') {
        key = reimplace_var_env(command_array, shell, i);
        if (key != NULL) {
            mini_printf("%s: Undefined variable.\n", key);
            free(key);
            shell->last_return = 1;
            return 1;
        }
    }
    return 0;
}

int explore_var_env(char **command_array, shell_t *shell)
{
    for (int i = 0; i < my_strlen_array(command_array); i++)
        if (error_var_env(command_array, i, shell))
            return 1;
    return 0;
}

static bool parse_multiple_commands_aux(shell_t *shell,
    char **command_array_sep)
{
    char **command_array;

    shell->fd_input = -1;
    shell->ind = -1;
    for (int i = 0; i < my_strlen_array(command_array_sep); i++) {
        command_array = sep_str(command_array_sep[i], 2, "\t", " ");
        if (explore_var_env(command_array, shell)) {
            free_word_array(command_array);
            return false;
        }
        pipe(shell->pipefd);
        command_interpreter(command_array, shell, command_array_sep, i);
        close(shell->fd_input);
        shell->fd_input = shell->pipefd[0];
        close(shell->pipefd[1]);
        free_word_array(command_array);
    }
    return print_fd(shell);
}

static void parse_multiple_commands(char *input, shell_t *shell)
{
    char **command_array_sep;
    char **multiple_commands = sep_str(input, 1, ";");

    for (int i = 0; i < my_strlen_array(multiple_commands); i++) {
        shell->separators = NULL;
        get_command_separators(shell, multiple_commands[i]);
        command_array_sep = sep_str(multiple_commands[i], 3, "|", "<", ">");
        if (command_array_sep == NULL || command_array_sep[0] == NULL) {
            free_word_array(command_array_sep);
            continue;
        }
        if (!parse_multiple_commands_aux(shell, command_array_sep))
            i = my_strlen_array(multiple_commands);
        free_word_array(shell->separators);
        free_word_array(command_array_sep);
    }
    free_word_array(multiple_commands);
}

int shell_interface(shell_t *shell)
{
    char *input;

    while (!shell->exit) {
        if (isatty(0))
            mini_printf("$> ");
        input = my_scanf();
        if (input == NULL)
            return 1;
        if ((my_strlen(input) == 1 && input[0] == '\n') ||
        error_handling_command(shell, input)) {
            free(input);
            continue;
        }
        parse_multiple_commands(input, shell);
        free(input);
    }
    return 0;
}
