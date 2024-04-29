/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-42sh-florian.reynaud
** File description:
** alias.c
*/

#include "../../include/mysh.h"

static void print_aliases(alias_t *alias)
{
    if (alias == NULL)
        return;
    print_aliases(alias->next);
    mini_printf("%s\t", alias->keyword);
    if (my_strlen_array(alias->replacement) == 1) {
        mini_printf("%s\n", alias->replacement[0]);
        return;
    }
    mini_printf("(");
    for (int i = 0; alias->replacement[i] != NULL; i++) {
        mini_printf("%s%s", alias->replacement[i],
        i == my_strlen_array(alias->replacement) - 1 ? ")\n" : " ");
    }
}

static void show_alias(alias_t *head, char *to_find)
{
    alias_t *alias = find_alias(head, to_find);

    if (alias == NULL)
        return;
    for (int i = 0; alias->replacement[i] != NULL; i++) {
        mini_printf("%s%s", alias->replacement[i],
        i == my_strlen_array(alias->replacement) - 1 ? "\n" : " ");
    }
}

static void new_alias(shell_t *shell, char **args)
{
    alias_t *new_alias = find_alias(shell->alias, args[1]);

    if (new_alias == NULL) {
        new_alias = malloc(sizeof(alias_t));
        new_alias->keyword = my_strdup(args[1]);
        new_alias->replacement = my_tabdup(args + 2);
        new_alias->next = shell->alias;
        shell->alias = new_alias;
    } else {
        free_word_array(new_alias->replacement);
        new_alias->replacement = my_tabdup(args + 2);
    }
}

int my_alias(char **args, shell_t *shell)
{
    if (my_strlen_array(args) == 1) {
        print_aliases(shell->alias);
        shell->last_return = 0;
        return 1;
    }
    if (my_strlen_array(args) == 2) {
        show_alias(shell->alias, args[1]);
        shell->last_return = 0;
        return 1;
    }
    new_alias(shell, args);
    shell->last_return = 0;
    return 1;
}
