/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-florian.reynaud
** File description:
** execute
*/

#include "../../include/mysh.h"
#include <unistd.h>

const operation_t operation[] = {
    {COMMAND, execute_normal},
    {PIPE, execute_ast_pipe},
    {SEMICOLON, execute_ast_semicolon},
    {REDIRECTION_RIGTH, execute_redirect},
    {REDIRECTION_LEFT, execute_input},
    {DOUBLE_RIGHT, execute_append},
    {DOUBLE_LEFT, execute_input_here},
    {AND_OP, execute_and_operator},
    {OR_OP, execute_or_operator},
    {NONE, NULL}
};

int execute_ast_node(ast_node_t *node, shell_t *shell)
{
    for (int i = 0; operation[i].op != NONE; i++) {
        if (operation[i].op == node->type)
            return operation[i].f(node, shell);
    }
    return execute_ast_semicolon(node, shell);
}
