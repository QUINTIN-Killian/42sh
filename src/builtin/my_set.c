/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_set.c
*/

#include "../../include/mysh.h"

variables_t *find_variable(variables_t *node, char *name)
{
    if (node == NULL)
        return NULL;
    if (strcmp(node->name, name) == 0)
        return node;
    return find_variable(node->next, name);
}

char *get_variable_value(variables_t *node, char *name)
{
    if (node == NULL)
        return NULL;
    if (strcmp(node->name, name) == 0)
        return strdup(node->value);
    return get_variable_value(node->next, name);
}

void destroy_variables(variables_t *node)
{
    if (node == NULL)
        return;
    destroy_variables(node->next);
    free(node->name);
    free(node->value);
    free(node);
}

static void print_variables(variables_t *variables)
{
    if (variables == NULL)
        return;
    print_variables(variables->next);
    mini_printf("%s\t%s\n", variables->name, variables->value);
}

static void new_variable(char **args, shell_t *shell)
{
    variables_t *var;
    char *name = string_to_delims(args[1], "=");

    var = find_variable(shell->variables, name);
    if (var == NULL) {
        var = malloc(sizeof(variables_t));
        var->name = strdup(name);
        var->next = shell->variables;
        shell->variables = var;
    } else {
        free(var->value);
    }
    if (strlen(name) == strlen(args[1]))
        var->value = strdup("");
    else
        var->value = strdup(args[1] + strlen(name) + 1);
    free(name);
}

int my_set(char **args, shell_t *shell)
{
    if (my_strlen_array(args) == 1) {
        print_variables(shell->variables);
        shell->last_return = 0;
        return 1;
    }
    new_variable(args, shell);
    shell->last_return = 0;
    return 1;
}
