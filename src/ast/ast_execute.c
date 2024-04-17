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

static int execute_ast_semicolon(ast_node_t *node, shell_t *shell)
{
    int rv = 0;

    if (node->left != NULL)
        rv = execute_ast_node(node->left, shell);
    if (node->right != NULL)
        rv = execute_ast_node(node->right, shell);
    return rv;
}

static int execute_ast_pipe(ast_node_t *node, shell_t *shell)
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

int is_builtin(char **args, shell_t *shell)
{
    if (my_strcmp(args[0], "cd") == 0)
        return my_cd(args, shell);
    if (my_strcmp(args[0], "env") == 0)
        return my_env(args, shell);
    if (my_strcmp(args[0], "setenv") == 0)
        return my_setenv(args, shell);
    if (my_strcmp(args[0], "unsetenv") == 0)
        return my_unsetenv(args, shell);
    if (my_strcmp(args[0], "exit") == 0)
        return my_exit(args, shell);
    return 0;
}

int execute_ast_node(ast_node_t *node, shell_t *shell)
{
    switch (node->type) {
        case PIPE:
            return execute_ast_pipe(node, shell);
        case SEMICOLON:
            return execute_ast_semicolon(node, shell);
        case COMMAND:
            return execute_normal(node, shell);
        case REDIRECTION_RIGTH:
            return execute_redirect(node, shell);
        case REDIRECTION_LEFT:
            return execute_input(node, shell);
        case DOUBLE_RIGHT:
            return execute_append(node, shell);
        case DOUBLE_LEFT:
            return execute_input_here(node, shell);
        default:
            return execute_ast_semicolon(node, shell);
    }
}
