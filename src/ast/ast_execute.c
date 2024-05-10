/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-florian.reynaud
** File description:
** execute
*/

#include "../../include/mysh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int execute_ast_semicolon(ast_node_t *node, shell_t *shell)
{
    int rv = 0;

    if (node->left != NULL)
        rv = execute_ast_node(node->left, shell);
    if (node->right != NULL)
        rv = execute_ast_node(node->right, shell);
    return rv;
}

int execute_ast_pipe(ast_node_t *node, shell_t *shell)
{
    int rv = 0;
    int fdtmp = dup(0);

    pipe(shell->pipefd);
    if (node->left != NULL){
        rv = execute_pipe(node->left, shell);
    }
    close(shell->pipefd[1]);
    dup2(shell->pipefd[0], STDIN_FILENO);
    close(shell->pipefd[0]);
    if (node->right != NULL)
        rv = execute_ast_node(node->right, shell);
    dup2(fdtmp, 0);
    close(fdtmp);
    return rv;
}

int execute_and_operator(ast_node_t *node, shell_t *shell)
{
    int rv = 0;

    if (node->left != NULL)
        rv = execute_ast_node(node->left, shell);
    if (shell->last_return == 0 && node->right != NULL)
        rv = execute_ast_node(node->right, shell);
    return rv;
}

int execute_or_operator(ast_node_t *node, shell_t *shell)
{
    int rv = 0;

    if (node->left != NULL)
        rv = execute_ast_node(node->left, shell);
    if (shell->last_return != 0 && node->right != NULL)
        rv = execute_ast_node(node->right, shell);
    return rv;
}
