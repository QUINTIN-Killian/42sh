/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-42sh-florian.reynaud
** File description:
** my_unalias.c
*/

#include "../../include/mysh.h"

static void delete_alias(alias_t **head, alias_t *curr, alias_t *prev)
{
    if (prev == NULL)
        *head = (*head)->next;
    else
        prev->next = curr->next;
    free(curr->keyword);
    free_word_array(curr->replacement);
    free(curr);
}

static void find_delete_alias(alias_t **head, char *to_find)
{
    alias_t *curr = *head;
    alias_t *prev = NULL;

    for (; curr != NULL; curr = curr->next) {
        if (my_strcmp(curr->keyword, to_find) == 0) {
            delete_alias(head, curr, prev);
            return;
        }
        prev = curr;
    }
}

int my_unalias(char **args, shell_t *shell)
{
    for (int i = 1; args[i] != NULL; i++) {
        find_delete_alias(&shell->alias, args[i]);
    }
    shell->last_return = 0;
    return 1;
}
