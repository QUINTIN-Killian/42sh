/*
** EPITECH PROJECT, 2024
** mini_shell2
** File description:
** command separators management
** command_separators
*/

#include "../include/mysh.h"

char **realloc_tab_plus_one(char **tab)
{
    char **ans = malloc(sizeof(char *) * (my_strlen_array(tab) + 2));

    for (int i = 0; i < my_strlen_array(tab); i++)
        ans[i] = my_strdup(tab[i]);
    ans[my_strlen_array(tab)] = NULL;
    ans[my_strlen_array(tab) + 1] = NULL;
    return ans;
}

static bool is_pipe(shell_t *shell, char *command, int i)
{
    char **new_tab;

    if (command[i] == '|') {
        new_tab = realloc_tab_plus_one(shell->separators);
        new_tab[my_strlen_array(shell->separators)] = my_strdup("|");
        free_word_array(shell->separators);
        shell->separators = my_tabdup(new_tab);
        free_word_array(new_tab);
        return true;
    }
    return false;
}

static bool is_right_redirection(shell_t *shell, char *command, int i)
{
    char **new_tab;

    if (command[i] == '>' && i < my_strlen(command)
    - 1 && command[i + 1] == '>') {
        new_tab = realloc_tab_plus_one(shell->separators);
        new_tab[my_strlen_array(shell->separators)] = my_strdup(">>");
        free_word_array(shell->separators);
        shell->separators = my_tabdup(new_tab);
        free_word_array(new_tab);
        return true;
    }
    if (command[i] == '>') {
        new_tab = realloc_tab_plus_one(shell->separators);
        new_tab[my_strlen_array(shell->separators)] = my_strdup(">");
        free_word_array(shell->separators);
        shell->separators = my_tabdup(new_tab);
        free_word_array(new_tab);
        return true;
    }
    return false;
}

static bool is_left_redirection(shell_t *shell, char *command, int i)
{
    char **new_tab;

    if (command[i] == '<' && i < my_strlen(command)
    - 1 && command[i + 1] == '<') {
        new_tab = realloc_tab_plus_one(shell->separators);
        new_tab[my_strlen_array(shell->separators)] = my_strdup("<<");
        free_word_array(shell->separators);
        shell->separators = my_tabdup(new_tab);
        free_word_array(new_tab);
        return true;
    }
    if (command[i] == '<') {
        new_tab = realloc_tab_plus_one(shell->separators);
        new_tab[my_strlen_array(shell->separators)] = my_strdup("<");
        free_word_array(shell->separators);
        shell->separators = my_tabdup(new_tab);
        free_word_array(new_tab);
        return true;
    }
    return false;
}

void get_command_separators(shell_t *shell, char *command)
{
    for (int i = 0; i < my_strlen(command); i++) {
        if (is_pipe(shell, command, i))
            continue;
        if (is_right_redirection(shell, command, i))
            continue;
        if (is_left_redirection(shell, command, i))
            continue;
    }
}
