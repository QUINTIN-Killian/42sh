/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** shell management
** shell
*/

#include "../include/mysh.h"

static int continue_shell_interface_aux(shell_t *shell, char **input)
{
    if (reimplace_history_getter(shell, input)) {
        free(*input);
        shell->last_return = 1;
        return 1;
    }
    add_history(&shell->history, *input);
    if (error_handling_input(shell, *input)) {
        free(*input);
        return 1;
    }
    return 0;
}

static int continue_shell_interface(shell_t *shell, char **input)
{
    char **tab;

    if ((my_strlen(*input) == 1 && *input[0] == '\n')) {
        free(*input);
        return 1;
    }
    tab = sep_str(*input, 2, " ", "\t");
    if (tab == NULL) {
        free(*input);
        return 1;
    }
    free_word_array(tab);
    return continue_shell_interface_aux(shell, input);
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
        if (continue_shell_interface(shell, &input))
            continue;
        input = replace_variables(shell, input);
        if (input == NULL)
            continue;
        shell->ast = build_ast(input);
        execute_ast_node(shell->ast, shell);
        free_ast_node(shell->ast);
        free(input);
    }
    return 0;
}
