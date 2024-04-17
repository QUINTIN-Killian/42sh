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
        error_handling_input(shell, input)) {
            free(input);
            continue;
        }
        shell->ast = build_ast(input);
        execute_ast_node(shell->ast, shell);
        free_ast_node(shell->ast);
        free(input);
    }
    return 0;
}
