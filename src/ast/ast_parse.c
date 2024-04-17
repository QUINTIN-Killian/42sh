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

static char *clear_str(char *str)
{
    int i = 0;
    char *temp;
    int len = my_strlen(str);
    int c = len - 1;

    for (; str[i] == ' '; i++);
    for (; str[c] == ' '; c--);
    c -= i - 1;
    temp = malloc(sizeof(char) * (c + 1));
    for (int j = 0; j < c; j++){
        temp[j] = str[i];
        i++;
        temp[j + 1] = '\0';
    }
    return temp;
}

static int pat_to_enum(char *pat)
{
    if (my_strcmp(pat, ">") == 0)
        return REDIRECTION_RIGTH;
    if (my_strcmp(pat, "<") == 0)
        return REDIRECTION_LEFT;
    if (my_strcmp(pat, "|") == 0)
        return PIPE;
    if (my_strcmp(pat, ";") == 0)
        return SEMICOLON;
    if (my_strcmp(pat, ">>") == 0)
        return DOUBLE_RIGHT;
    if (my_strcmp(pat, "<<") == 0)
        return DOUBLE_LEFT;
    return 0;
}

void ast_parse(ast_node_t *node, char *pat)
{
    for (int i = 0; node->value[i] != '\0'; i++) {
        if (node->type != COMMAND)
            break;
        if (my_strncmp(&node->value[i], pat, my_strlen(pat)) == 0) {
            node->left = create_ast_node(COMMAND,
                my_strndup(node->value, i));
            node->right = create_ast_node(COMMAND,
                my_strdup(clear_str(&node->value[i + my_strlen(pat)])));
            node->type = pat_to_enum(pat);
        }
    }
    if (node->left != NULL)
        ast_parse(node->left, pat);
    if (node->right != NULL)
        ast_parse(node->right, pat);
}
