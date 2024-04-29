/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** alias.c
*/

#include "../include/mysh.h"

alias_t *find_alias(alias_t *node, char *to_find)
{
    if (node == NULL || to_find == NULL)
        return NULL;
    if (my_strcmp(node->keyword, to_find) == 0)
        return node;
    return find_alias(node->next, to_find);
}

// NOTE: This function will be called before the initialization
// of every command. Replaces keywords with known replacements.
void replace_aliases(char ***args, shell_t *shell)
{
    alias_t *alias;
    char **new_args;
    uint32_t i;

    if (args == NULL)
        return;
    alias = find_alias(shell->alias, *args[0]);
    if (alias == NULL)
        return;
    new_args = malloc((my_strlen_array(*args) - 1 +
    my_strlen_array(alias->replacement)) * sizeof(char *) + sizeof(NULL));
    for (i = 0; alias->replacement[i] != NULL; i++)
        new_args[i] = my_strdup(alias->replacement[i]);
    for (int j = 1; (*args)[j] != NULL; j++) {
        new_args[i] = my_strdup((*args)[j]);
        i++;
    }
    new_args[i] = NULL;
    free_word_array(*args);
    *args = new_args;
}

void destroy_aliases(alias_t *alias)
{
    if (alias == NULL)
        return;
    destroy_aliases(alias->next);
    free(alias->keyword);
    free_word_array(alias->replacement);
    free(alias);
}
