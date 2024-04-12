/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** main file
** main
*/

#include "../include/mysh.h"

static void init_shell_struct(shell_t *shell, int ac, char **av, char **env)
{
    env_t *node;

    shell->exit = 0;
    shell->head = NULL;
    for (int i = 0; i < my_strlen_array(env); i++) {
        node = add_env(env[i]);
        node->next = shell->head;
        shell->head = node;
    }
    shell->ac = ac;
    shell->av = av;
    shell->last_return = 0;
}

static void destroy_shell_struct(shell_t *shell)
{
    env_t *tmp;

    while (shell->head != NULL) {
        tmp = shell->head;
        shell->head = shell->head->next;
        free(tmp->env);
        free(tmp);
    }
}

void print_word_array(char **word_array)
{
    if (word_array == NULL) {
        my_putstr("NULL\n");
        return;
    }
    for (int i = 0; i < my_strlen_array(word_array); i++) {
        my_putstr(word_array[i]);
        my_putchar('\n');
    }
}

int main(int ac, char **av, char **env)
{
    shell_t shell;

    init_shell_struct(&shell, ac, av, env);
    shell_interface(&shell);
    destroy_shell_struct(&shell);
    return shell.last_return;
    
}
