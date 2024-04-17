/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-florian.reynaud
** File description:
** ast
*/

#include "../../include/my.h"
#include "../../include/mysh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ast_node_t *create_ast_node(TokenType_t type, char *value)
{
    ast_node_t *node = (ast_node_t *)malloc(sizeof(ast_node_t));

    node->type = type;
    node->value = my_strdup(value);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_ast_node(ast_node_t *node)
{
    free(node->value);
    if (node->left != NULL)
        free_ast_node(node->left);
    if (node->right != NULL)
        free_ast_node(node->right);
    free(node);
}

static void put_node_value(ast_node_t *node)
{
    my_putstr("|-- ");
    switch (node->type) {
        case SEMICOLON:
            my_putstr(";");
            break;
        case PIPE:
            my_putstr("P");
            break;
        case REDIRECTION_RIGTH:
            my_putstr(">");
            break;
        case REDIRECTION_LEFT:
            my_putstr("<");
            break;
        default:
            my_putstr(node->value);
    }
    my_putstr("\n");
}

static void print_ast_tree(ast_node_t *node, int level)
{
    if (node == NULL)
        return;
    print_ast_tree(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        my_putstr("    ");
    }
    put_node_value(node);
    print_ast_tree(node->left, level + 1);
}

ast_node_t *build_ast(char *input)
{
    ast_node_t *root = create_ast_node(COMMAND, input);

    ast_parse(root, ";");
    ast_parse(root, "|");
    ast_parse(root, ">>");
    ast_parse(root, "<<");
    ast_parse(root, ">");
    ast_parse(root, "<");
    return root;
}
