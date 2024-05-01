/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** create a new environment variable
** my_setenv
*/

#include "../../include/mysh.h"

static int error_handling_key_setenv(char *key)
{
    if ((key[0] < 'A' || (key[0] > 'Z' && key[0] < 'a') || key[0] > 'z') &&
    key[0] != '_') {
        mini_fdprintf(2, "setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    for (int i = 0; i < my_strlen(key); i++) {
        if ((key[i] < '0' || (key[i] > '9' && key[i] < 'A') ||
        (key[i] > 'Z' && key[i] < 'a') || key[i] > 'z') && key[i] != '_') {
            mini_fdprintf(2,
            "setenv: Variable name must contain alphanumeric characters.\n");
            return 1;
        }
    }
    return 0;
}

static char *error_handling_setenv(char **command_array, shell_t *shell)
{
    if (my_strlen_array(command_array) == 1) {
        free(command_array[0]);
        command_array[0] = my_strdup("env");
        my_env(command_array, shell);
        return NULL;
    }
    if (my_strlen_array(command_array) == 2 &&
    !error_handling_key_setenv(command_array[1]))
        return concat_2_str(command_array[1], "=");
    if (my_strlen_array(command_array) == 3 &&
    !error_handling_key_setenv(command_array[1]))
        return concat_str(3, command_array[1], "=", command_array[2]);
    shell->last_return = 1;
    return NULL;
}

env_t *is_existing_env(shell_t *shell, char *key)
{
    env_t *node = shell->head;

    while (node != NULL) {
        if (my_strncmp(node->env, key, my_strlen(key)) == 0 &&
        node->env[my_strlen(key)] == '=')
            return node;
        node = node->next;
    }
    return NULL;
}

int my_setenv(char **command_array, shell_t *shell)
{
    env_t *node;
    char *env = error_handling_setenv(command_array, shell);

    if (env == NULL)
        return 1;
    node = is_existing_env(shell, command_array[1]);
    if (node == NULL) {
        node = add_env(env);
        node->next = shell->head;
        shell->head = node;
    } else {
        free(node->env);
        node->env = my_strdup(env);
    }
    free(env);
    shell->last_return = 0;
    return 1;
}
