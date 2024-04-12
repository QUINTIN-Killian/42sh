/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** clean a string by deleting all useless spaces
** clean_str
*/

#include "my.h"

static char *create_ans(char **tmp, int len_total)
{
    int ind = 0;
    char *ans = malloc(sizeof(char) * (len_total + 1));

    for (int i = 0; i < my_strlen_array(tmp); i++) {
        for (int j = 0; j < my_strlen(tmp[i]); j++) {
            ans[ind] = tmp[i][j];
            ind++;
        }
    }
    ans[len_total] = '\0';
    return ans;
}

char *clean_str(char *str, int destroy)
{
    char **tmp;
    int len_total = 0;
    char *ans;

    if (str == NULL)
        return NULL;
    tmp = separate_words_on_spaces(str);
    if (destroy)
        free(str);
    if (tmp == NULL)
        return NULL;
    for (int i = 0; i < my_strlen_array(tmp); i++)
        len_total += my_strlen(tmp[i]);
    len_total += my_strlen_array(tmp) - 1;
    ans = create_ans(tmp, len_total);
    free_word_array(tmp);
    return ans;
}
