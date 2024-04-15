/*
** EPITECH PROJECT, 2024
** 42sh-private
** File description:
** insert_elt_in_tab
*/

#include "my.h"

char **insert_elt_in_tab_plus_one(char **tab, char *elt)
{
    char **tmp = my_tabdup(tab);

    free_word_array(tab);
    tab = malloc(sizeof(char *) * (my_strlen_array(tmp) + 2));
    for (int i = 0; i < my_strlen_array(tmp); i++)
        tab[i] = my_strdup(tmp[i]);
    tab[my_strlen_array(tmp)] = my_strdup(elt);
    tab[my_strlen_array(tmp) + 1] = NULL;
    free_word_array(tmp);
    return tab;
}
