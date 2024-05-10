/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_unset.c
*/

#include "../../include/mysh.h"

static void delete_var(variables_t **head, variables_t *curr,
    variables_t *prev)
{
    if (prev == NULL) {
        *head = (*head)->next;
    } else {
        prev->next = curr->next;
    }
    free(curr->name);
    free(curr->value);
    free(curr);
}

static void delete_variable(variables_t **head, char *name)
{
    variables_t *prev = NULL;

    for (variables_t *curr = *head; curr != NULL; curr = curr->next) {
        if (strcmp(curr->name, name) == 0) {
            delete_var(head, curr, prev);
            return;
        }
        prev = curr;
    }
}

int my_unset(char **args, shell_t *shell)
{
    for (int i = 1; args[i] != NULL; i++) {
        delete_variable(&shell->variables, args[i]);
    }
    shell->last_return = 0;
    return 1;
}
