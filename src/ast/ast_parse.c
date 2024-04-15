/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-florian.reynaud
** File description:
** parse
*/

#include "../../include/my.h"
#include "../../include/mysh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ast_parse_semicolon(ast_node *node)
{
    for (int i = 0; node->value[i] != '\0'; i++) {
        if (node->type != COMMAND)
            break;
        if (node->value[i] == ';') {
            node->left = create_ast_node(COMMAND,
                my_strndup(node->value, i));
            node->right = create_ast_node(COMMAND,
                my_strdup(&node->value[i + 1]));
            node->type = SEMICOLON;
        }
    }
    if (node->left != NULL)
        ast_parse_semicolon(node->left);
    if (node->right != NULL)
        ast_parse_semicolon(node->right);
}

void ast_parse_pipe(ast_node *node)
{
    for (int i = 0; node->value[i] != '\0'; i++) {
        if (node->type != COMMAND)
            break;
        if (node->value[i] == '|') {
            node->left = create_ast_node(COMMAND,
                my_strndup(node->value, i));
            node->right = create_ast_node(COMMAND,
                my_strdup(&node->value[i + 1]));
            node->type = PIPE;
        }
    }
    if (node->left != NULL)
        ast_parse_pipe(node->left);
    if (node->right != NULL)
        ast_parse_pipe(node->right);
}

void ast_parse_redirection_rigth(ast_node *node)
{
    for (int i = 0; node->value[i] != '\0'; i++) {
        if (node->type != COMMAND)
            break;
        if (node->value[i] == '>') {
            node->left = create_ast_node(COMMAND,
                my_strndup(node->value, i));
            node->right = create_ast_node(COMMAND,
                my_strdup(&node->value[i + 1]));
            node->type = REDIRECTION_RIGTH;
        }
    }
    if (node->left != NULL)
        ast_parse_redirection_rigth(node->left);
    if (node->right != NULL)
        ast_parse_redirection_rigth(node->right);
}

void ast_parse_redirection_left(ast_node *node)
{
    for (int i = 0; node->value[i] != '\0'; i++) {
        if (node->type != COMMAND)
            break;
        if (node->value[i] == '<') {
            node->left = create_ast_node(COMMAND,
                my_strndup(node->value, i));
            node->right = create_ast_node(COMMAND,
                my_strdup(&node->value[i + 1]));
            node->type = REDIRECTION_LEFT;
        }
    }
    if (node->left != NULL)
        ast_parse_redirection_left(node->left);
    if (node->right != NULL)
        ast_parse_redirection_left(node->right);
}
