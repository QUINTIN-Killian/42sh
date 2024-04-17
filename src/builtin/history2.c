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

static void destroy_double_node(history_t *node)
{
    history_t *tmp = node->next;

    node->next = node->next->next;
    free(tmp->command);
    free(tmp->ctime);
    free(tmp);
}

void add_history(history_t **history, char *command)
{
    history_t *node = *history;
    time_t mytime = time(NULL);
    char *time_str = ctime(&mytime);

    if (*history == NULL) {
        *history = create_new_history_node(1, time_str, command, NULL);
        return;
    }
    if (my_strcmp(node->command, command) == 0)
        *history = node->next;
    while (node->next != NULL) {
        if (my_strcmp(node->next->command, command) == 0) {
            destroy_double_node(node);
            continue;
        }
        node = node->next;
    }
    node->next = create_new_history_node(node->id + 1, time_str, command,
    NULL);
}

int history(char **command_array, shell_t *shell)
{
    if (my_strlen_array(command_array) > 3) {
        mini_printf("history: Too many arguments.\n");
        shell->last_return = 1;
        return 1;
    }
    for (int i = 1; i < my_strlen_array(command_array); i++) {
        if (!my_str_isnum(command_array[i])) {
            mini_printf("history: Badly formed number.\n");
            shell->last_return = 1;
            return 1;
        }
    }
    if (my_strlen_array(command_array) == 1)
        print_history(1, &shell->history, get_len_history(&shell->history));
    else
        print_history(1, &shell->history,
        convert_str_in_int(command_array[1]));
    shell->last_return = 0;
    return 1;
}
