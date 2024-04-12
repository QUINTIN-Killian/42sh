/*
** EPITECH PROJECT, 2024
** robot_factory
** File description:
** separate_words
*/

#include "my.h"

static int is_sep(char c, char const *sep)
{
    for (int i = 0; i < my_strlen(sep); i++)
        if (c == sep[i])
            return 1;
    return 0;
}

static int det_nb_word(separate_words_t *infos)
{
    int ans = 0;
    int a = 1;

    for (int i = 0; i < my_strlen(infos->str); i++) {
        if (!is_sep(infos->str[i], infos->sep) && a == 1) {
            ans++;
            a = 0;
        }
        if (is_sep(infos->str[i], infos->sep)) {
            a = 1;
        }
    }
    return ans;
}

static int det_len_word(char const *str, int ind, char const *sep)
{
    int ans = 0;

    while (!is_sep(str[ind + ans], sep) && (ind + ans) < my_strlen(str)) {
        ans++;
    }
    return ans;
}

static void set_word(separate_words_t *infos, int *start, int *ind_tab)
{
    int i;

    while (*start < my_strlen(infos->str)) {
        i = 0;
        infos->tab[*ind_tab] = malloc(sizeof(char) *
        det_len_word(infos->str, *start, infos->sep) + 1);
        while (*start < my_strlen(infos->str) &&
        !is_sep(infos->str[*start], infos->sep)) {
            infos->tab[*ind_tab][i] = infos->str[*start];
            i++;
            *start = *start + 1;
        }
        infos->tab[*ind_tab][i] = '\0';
        *start = *start + 1;
        *ind_tab = *ind_tab + 1;
        while (*start < my_strlen(infos->str) &&
        is_sep(infos->str[*start], infos->sep))
            *start = *start + 1;
    }
}

char **separate_words(char const *str, char const *sep)
{
    separate_words_t infos;
    int ind_tab = 0;
    int start = 0;
    int nb_words;

    infos.str = str;
    infos.sep = sep;
    nb_words = det_nb_word(&infos);
    if (my_strlen(infos.str) == 0 || nb_words == 0)
        return NULL;
    infos.tab = malloc(sizeof(char *) * (nb_words + 1));
    while (start < my_strlen(infos.str) && is_sep(infos.str[start], infos.sep))
        start++;
    set_word(&infos, &start, &ind_tab);
    infos.tab[nb_words] = NULL;
    return infos.tab;
}
