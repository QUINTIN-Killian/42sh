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

static void replace_args(char ***args, alias_t *alias)
{
    char **new_args;
    uint32_t i;

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

// NOTE: This function will be called before the initialization
// of every command. Replaces keywords with known replacements.
int replace_aliases(char ***args, shell_t *shell, my_stack_t **alias_stack)
{
    alias_t *alias;

    if (*args == NULL)
        return 0;
    alias = find_alias(shell->alias, (*args)[0]);
    if (alias == NULL)
        return 0;
    if (is_in_stack(*alias_stack, alias->replacement[0]))
        return 1;
    add_in_stack(alias_stack, (*args)[0]);
    replace_args(args, alias);
    return replace_aliases(args, shell, alias_stack);
}

int handle_aliases(char ***args, shell_t *shell)
{
    my_stack_t *alias_stack = NULL;
    int ex = replace_aliases(args, shell, &alias_stack);

    destroy_stack(alias_stack);
    if (ex == 1) {
        fprintf(stderr, "Alias loop.\n");
        shell->last_return = 1;
        free_word_array(*args);
        return 1;
    }
    return 0;
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
