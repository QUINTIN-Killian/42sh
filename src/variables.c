/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** variables.c
*/

#include "../include/mysh.h"

#include <string.h>

static char *get_variable(shell_t *shell, char *input, int *i)
{
    char *token = string_to_delims(input, " \t/;|&><$\n\"'");
    char *var;

    if (token == NULL)
        return NULL;
    // get local variable
    var = get_env_value(shell, token);
    if (var == NULL)
        fprintf(stderr, "%s: Undefined variable.\n", token);
    *i += strlen(token);
    free(token);
    return var;
}

static int handle_variables(char *var, char **new_input, int *index)
{
    char *temp = *new_input;

    if (var == NULL) {
        free(var);
        free(*new_input);
        return 1;
    }
    *new_input = concat(*new_input, var);
    free(temp);
    *index = strlen(*new_input);
    free(var);
    return 0;
}

static void update_input(char **new_input, char *input, int *index, int i)
{
    *new_input = realloc(*new_input, *index + 2);
    (*new_input)[*index] = input[i];
    (*new_input)[*index + 1] = '\0';
    *index += 1;
}

char *replace_variables(shell_t *shell, char *input)
{
    char *new_input = NULL;
    char *var;
    int index = 0;

    if (!char_in_string('$', input))
        return input;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != '$') {
            update_input(&new_input, input, &index, i);
            continue;
        }
        var = get_variable(shell, input + i + 1, &i);
        if (handle_variables(var, &new_input, &index)) {
            free(input);
            shell->last_return = 1;
            return NULL;
        }
    }
    free(input);
    return new_input;
}
