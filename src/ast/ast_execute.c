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

// static int execute_ast_command(ast_node *node, char ***env)
// {
//     int rv = 0;

//     if (node->left != NULL)
//         rv = execute_ast_node(node->left, env);
//     if (node->value)
//         rv = do_command(node->value, env);
//     if (node->right != NULL)
//         rv = execute_ast_node(node->right, env);
//     return rv;
// }

static int execute_ast_semicolon(ast_node *node, shell_t *shell)
{
    int rv = 0;

    if (node->left != NULL)
        rv = execute_ast_node(node->left, shell);
    if (node->right != NULL)
        rv = execute_ast_node(node->right, shell);
    return rv;
}

// static int execute_ast_pipe(ast_node *node, char ***env)
// {
//     int rv = 0;
//     int fdtmp = dup(0);
//     int pipefd[2];

//     pipe(pipefd);
//     if (node->left != NULL)
//         rv = do_command_pipe(node->left->value, env, pipefd);
//     close(pipefd[1]);
//     dup2(pipefd[0], STDIN_FILENO);
//     close(pipefd[0]);
//     if (node->right != NULL)
//         rv = execute_ast_node(node->right, env);
//     dup2(fdtmp, 0);
//     close(fdtmp);
//     return rv;
// }

int execute_ast_node(ast_node *node, shell_t *shell)
{
    switch (node->type) {
        // case PIPE:
        //     return execute_ast_pipe(node, env);
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
            return  execute_ast_semicolon(node, shell);
    }
}
