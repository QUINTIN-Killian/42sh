/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** useful functions
** functions
*/

#include "../include/mysh.h"

static char *parse_value(char *env, int ind)
{
    int len = 0;
    char *value;

    for (int i = ind + 1; env[i] != '\0'; i++)
        len++;
    value = malloc(sizeof(char) * (len + 1));
    for (int i = ind + 1; env[i] != '\0'; i++)
        value[i - (ind + 1)] = env[i];
    value[len] = '\0';
    return value;
}

char *get_env_value(shell_t *shell, char *key)
{
    env_t *node = shell->head;

    while (node != NULL) {
        if (my_strncmp(node->env, key, my_strlen(key)) == 0 &&
        node->env[my_strlen(key)] == '=') {
            return parse_value(node->env, my_strlen(key));
        }
        node = node->next;
    }
    return NULL;
}

static int det_len_word(char const *str, int ind)
{
    int ans = 0;

    while (str[ind + ans] != ':' && (ind + ans) < my_strlen(str)) {
        ans++;
    }
    return ans;
}

char **convert_linked_list_in_word_array(shell_t *shell)
{
    env_t *node = shell->head;
    int len = 0;
    char **word_array;

    while (node != NULL) {
        len++;
        node = node->next;
    }
    word_array = malloc(sizeof(char *) * (len + 1));
    node = shell->head;
    for (int i = 0; i < len; i++) {
        word_array[i] = my_strdup(node->env);
        node = node->next;
    }
    word_array[len] = NULL;
    return word_array;
}

int count_occ_motif(char *str, char *motif)
{
    int ans = 0;
    char *tmp;

    for (int i = 0; i < my_strlen(str); i++) {
        if (i > my_strlen(str) - my_strlen(motif))
            return ans;
        tmp = parse_str(str, i, i + my_strlen(motif) - 1);
        if (my_strcmp(tmp, motif) == 0)
            ans++;
        free(tmp);
    }
    return ans;
}
