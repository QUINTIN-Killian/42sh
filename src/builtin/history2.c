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

void destroy_history_node(int id, char *command, history_t **history)
{
    history_t *node = *history;

    while (*history != NULL && my_strcmp(node->command, command) == 0 &&
    node->id != id) {
        *history = node->next;
        free(node->command);
        free(node->ctime);
        free(node);
        node = *history;
    }
    if (*history == NULL)
        return;
    while (node->next != NULL) {
        if (my_strcmp(node->next->command, command) == 0 && node->next->id
        != id) {
            destroy_double_node(node);
            continue;
        }
        node = node->next;
    }
}

static void clear_history(history_t **history)
{
    int len = get_len_history(history);
    history_t *tmp;

    while (len > 100) {
        tmp = *history;
        if (tmp == NULL)
            return;
        *history = tmp->next;
        free(tmp->command);
        free(tmp->ctime);
        free(tmp);
        len--;
    }
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
    while (node->next != NULL)
        node = node->next;
    node->next = create_new_history_node(node->id + 1, time_str, command,
    NULL);
    destroy_history_node(node->next->id, node->next->command, history);
    clear_history(history);
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

static char *get_history_command_by_command(history_t **history, char *input)
{
    history_t *node;

    *history = rev_history(history);
    node = *history;
    while (node != NULL) {
        if (my_strncmp(node->command, &(input[1]), my_strlen(&(input[1])))
        == 0) {
            mini_printf("%s\n", node->command);
            *history = rev_history(history);
            return node->command;
        }
        node = node->next;
    }
    *history = rev_history(history);
    mini_printf("%s: Event not found.\n", &(input[1]));
    return NULL;
}

static char *get_history_command_by_id(history_t **history, int id,
    char *input)
{
    history_t *node = *history;

    while (node != NULL) {
        if (node->id == id) {
            mini_printf("%s\n", node->command);
            return node->command;
        }
        node = node->next;
    }
    mini_printf("%s: Event not found.\n", &(input[1]));
    return NULL;
}

static char *get_history_command_by_id_minus(history_t **history, int id)
{
    history_t *node = *history;

    if (id <= 0 || id > get_len_history(history)) {
        mini_printf("%d: Event not found.\n", id);
        return NULL;
    }
    while (id != 1) {
        id--;
        node = node->next;
    }
    mini_printf("%s\n", node->command);
    return node->command;
}

char *get_history_id(history_t **history, char *input)
{
    int id = -1;

    if (input == NULL || my_strlen(input) <= 1 || input[0] != '!')
        return input;
    if (input[1] == '-' && my_str_isnum(&(input[2])))
        id = convert_str_in_int(&(input[2]));
    else if (my_str_isnum(&(input[1])))
        id = convert_str_in_int(&(input[1]));
    if (id != -1) {
        if (input[1] == '-') {
            id = get_len_history(history) + 1 - id;
            return get_history_command_by_id_minus(history, id);
        }
        return get_history_command_by_id(history, id, input);
    }
    return get_history_command_by_command(history, input);
}
