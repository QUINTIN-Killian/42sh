/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** stack.c
*/

#include "../include/mysh.h"

#include <stdbool.h>

void destroy_stack(my_stack_t *stack)
{
    if (stack == NULL)
        return;
    destroy_stack(stack->next);
    free(stack->value);
    free(stack);
}

void add_in_stack(my_stack_t **stack, char *value)
{
    my_stack_t *new_stack;

    if (*stack == NULL) {
        new_stack = malloc(sizeof(my_stack_t));
        new_stack->value = my_strdup(value);
        new_stack->next = NULL;
        *stack = new_stack;
        return;
    }
    add_in_stack(&(*stack)->next, value);
}

bool is_in_stack(my_stack_t *stack, char *to_find)
{
    if (stack == NULL)
        return false;
    if (my_strcmp(stack->value, to_find) == 0)
        return true;
    return is_in_stack(stack->next, to_find);
}
