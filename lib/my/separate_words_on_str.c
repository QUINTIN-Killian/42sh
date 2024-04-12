/*
** EPITECH PROJECT, 2024
** robot_factory
** File description:
** separate_words_on_str
*/

#include "my.h"

static int is_sep(char const *str, char const *sep, int ind)
{
    char *tmp = parse_str(str, ind, ind + my_strlen(sep) - 1);

    if (tmp == NULL)
        return 0;
    if (my_strcmp(sep, tmp) == 0) {
        free(tmp);
        return 1;
    }
    free(tmp);
    return 0;
}

static int det_nb_word(separate_words_t *infos)
{
    int ans = 0;
    int a = 1;

    for (int i = 0; i < my_strlen(infos->str); i++) {
        if (!is_sep(infos->str, infos->sep, i) && a == 1) {
            ans++;
            a = 0;
        }
        if (is_sep(infos->str, infos->sep, i)) {
            a = 1;
        }
    }
    return ans;
}

static int det_len_word(char const *str, int ind, char const *sep)
{
    int ans = 0;

    while (!is_sep(str, sep, ind + ans) && (ind + ans) < my_strlen(str)) {
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
        !is_sep(infos->str, infos->sep, *start)) {
            infos->tab[*ind_tab][i] = infos->str[*start];
            i++;
            *start = *start + 1;
        }
        infos->tab[*ind_tab][i] = '\0';
        *start = *start + 1;
        *ind_tab = *ind_tab + 1;
        while (*start < my_strlen(infos->str) &&
        is_sep(infos->str, infos->sep, *start))
            *start = *start + 1;
    }
}

char **separate_words_on_str(char const *str, char const *sep)
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
    while (start < my_strlen(infos.str) && is_sep(infos.str, infos.sep, start))
        start++;
    set_word(&infos, &start, &ind_tab);
    infos.tab[nb_words] = NULL;
    return infos.tab;
}
