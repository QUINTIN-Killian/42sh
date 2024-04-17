/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** shell management
** shell
*/

#include "../include/mysh.h"

static int continue_shell_interface(shell_t *shell, char *input)
{
    if ((my_strlen(input) == 1 && input[0] == '\n')) {
        free(input);
        return 1;
    }
    add_history(&shell->history, input);
    if (error_handling_input(shell, input)) {
        free(input);
        return 1;
    }
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
        if (continue_shell_interface(shell, input))
            continue;
        shell->ast = build_ast(input);
        execute_ast_node(shell->ast, shell);
        free_ast_node(shell->ast);
        free(input);
    }
    return 0;
}
