/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** separate_words_on_spaces
*/

#include "my.h"

static int det_nb_word(char const *str)
{
    int ans = 0;
    int a = 1;

    for (int i = 0; i < my_strlen(str); i++) {
        if (str[i] != ' ' && str[i] != '\t' && a == 1) {
            ans++;
            a = 0;
        }
        if (str[i] == ' ' || str[i] == '\t') {
            a = 1;
        }
    }
    return ans;
}

static int det_len_word(char const *str, int ind)
{
    int ans = 0;

    while (str[ind + ans] != ' ' && str[ind + ans] != '\t' &&
    (ind + ans) < my_strlen(str)) {
        ans++;
    }
    return ans;
}

static void set_word(char **tab, char const *str, int *start, int *ind_tab)
{
    int i;

    while (*start < my_strlen(str)) {
        i = 0;
        tab[*ind_tab] = malloc(sizeof(char) * det_len_word(str, *start) + 1);
        while (*start < my_strlen(str) && str[*start] != ' ' &&
        str[*start] != '\t') {
            tab[*ind_tab][i] = str[*start];
            i++;
            *start = *start + 1;
        }
        tab[*ind_tab][i] = '\0';
        *start = *start + 1;
        *ind_tab = *ind_tab + 1;
        while (*start < my_strlen(str) && (str[*start] == ' ' ||
        str[*start] == '\t'))
            *start = *start + 1;
    }
}

char **separate_words_on_spaces(char const *str)
{
    char **tab;
    int ind_tab = 0;
    int start = 0;
    int nb_words = det_nb_word(str);

    if (my_strlen(str) == 0 || nb_words == 0)
        return NULL;
    tab = malloc(sizeof(char *) * (nb_words + 1));
    while (start < my_strlen(str) && (str[start] == ' ' ||
    str[start] == '\t')) {
        start++;
    }
    set_word(tab, str, &start, &ind_tab);
    tab[nb_words] = NULL;
    return tab;
}
