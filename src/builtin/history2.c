/*
** EPITECH PROJECT, 2024
** 42sh-private
** File description:
** history2
*/

#include "../../include/mysh.h"

int get_len_history(history_t **history)
{
    history_t *node = *history;
    int len = 0;

    while (node != NULL) {
        len++;
        node = node->next;
    }
    return len;
}
