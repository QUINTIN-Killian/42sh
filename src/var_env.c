/*
** EPITECH PROJECT, 2024
** 42sh-private
** File description:
** environment variables management
** var_env
*/

#include "../include/mysh.h"

static char *reimplace_var_env(shell_t *shell, int i)
{
    char *key;

    if (my_strcmp(shell->command_array[i], "$?") == 0) {
        free(shell->command_array[i]);
        shell->command_array[i] = convert_int_to_str(shell->last_return);
        return NULL;
    }
    key = malloc(sizeof(char) * my_strlen(shell->command_array[i]));
    for (int j = 0; j < my_strlen(shell->command_array[i]) - 1; j++)
        key[j] = shell->command_array[i][j + 1];
    key[my_strlen(shell->command_array[i]) - 1] = '\0';
    free(shell->command_array[i]);
    shell->command_array[i] = get_env_value(shell, key);
    if (shell->command_array[i] == NULL)
        return key;
    free(key);
    return NULL;
}

static int error_var_env(int i, shell_t *shell)
{
    char *key;

    if (shell->command_array[i][0] == '$') {
        key = reimplace_var_env(shell, i);
        if (key != NULL) {
            mini_printf("%s: Undefined variable.\n", key);
            free(key);
            shell->last_return = 1;
            return 1;
        }
    }
    return 0;
}

int explore_var_env(shell_t *shell)
{
    for (int i = 0; i < my_strlen_array(shell->command_array); i++)
        if (error_var_env(i, shell))
            return 1;
    return 0;
}
