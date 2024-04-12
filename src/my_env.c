/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** print env variables
** env
*/

#include "../include/mysh.h"

env_t *add_env(char *env)
{
    env_t *node = malloc(sizeof(env_t));

    node->env = my_strdup(env);
    return node;
}

static void free_node(env_t *node)
{
    free(node->env);
    free(node);
}

static int is_first_node(shell_t *shell, char *key)
{
    env_t *node = shell->head;
    env_t *tmp;

    if (my_strncmp(node->env, key, my_strlen(key)) == 0 &&
    node->env[my_strlen(key)] == '=') {
        tmp = node;
        node = node->next;
        shell->head = node;
        free_node(tmp);
        return 1;
    }
    return 0;
}

int del_env(shell_t *shell, char *key)
{
    env_t *node = shell->head;
    env_t *tmp;

    if (is_first_node(shell, key))
        return 0;
    while (node->next != NULL) {
        if (my_strncmp(node->next->env, key, my_strlen(key)) == 0 &&
        node->next->env[my_strlen(key)] == '=') {
            tmp = node->next;
            node->next = node->next->next;
            free_node(tmp);
            return 0;
        }
        node = node->next;
    }
    return 1;
}

static int error_handling_env_aux(shell_t *shell, char **command_array,
    int ret, struct stat *st)
{
    if (ret != -1 && command_array[1][my_strlen(command_array[1]) - 1] == '/'){
        if (S_ISDIR(st->st_mode))
            mini_fdprintf(shell->pipefd[1], "’: Permission denied\n");
        else
            mini_fdprintf(shell->pipefd[1], "’: Not a directory\n");
        return 126;
    }
    return -1;
}

static int error_handling_env(shell_t *shell, char **command_array)
{
    struct stat st;
    int ret;

    ret = stat(command_array[1], &st);
    mini_fdprintf(shell->pipefd[1], "env: `%s", command_array[1]);
    if (command_array[1][my_strlen(command_array[1]) - 1] != '/') {
        mini_fdprintf(shell->pipefd[1], "’: No such file or directory\n");
        return 127;
    }
    if (ret == -1) {
        mini_fdprintf(shell->pipefd[1], "’: %s\n", strerror(errno));
        if (errno == 20)
            return 126;
        else
            return 127;
    }
    return error_handling_env_aux(shell, command_array, ret, &st);
}

int my_env(char **command_array, shell_t *shell)
{
    env_t *node;

    if (my_strlen_array(command_array) != 1) {
        shell->last_return = error_handling_env(shell, command_array);
        return 1;
    }
    node = shell->head;
    if (shell->ind >= my_strlen_array(shell->separators)) {
        while (node != NULL) {
            mini_printf("%s\n", node->env);
            node = node->next;
        }
    } else {
        while (node != NULL) {
            mini_fdprintf(shell->pipefd[1], "%s\n", node->env);
            node = node->next;
        }
    }
    shell->last_return = 0;
    return 0;
}

int change_var_env(shell_t *shell, char *key, char *new_env)
{
    env_t *node = shell->head;

    while (node != NULL) {
        if (my_strncmp(node->env, key, my_strlen(key)) == 0 &&
        node->env[my_strlen(key)] == '=') {
            free(node->env);
            node->env = my_strdup(new_env);
            free(new_env);
            return 0;
        }
        node = node->next;
    }
    node = add_env(new_env);
    node->next = shell->head;
    shell->head = node;
    free(new_env);
    return 1;
}
