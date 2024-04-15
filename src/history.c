/*
** EPITECH PROJECT, 2024
** 42sh-private
** File description:
** history
*/

#include "../include/mysh.h"

static history_t *create_new_history_node(int id, char *ctime, char *command,
    history_t *next)
{
    history_t *new_history = malloc(sizeof(history_t));

    new_history->id = id;
    new_history->ctime = my_strdup(ctime);
    new_history->command = command;
    new_history->next = next;
    return new_history;
}

static history_t *rev_history(history_t **history)
{
    history_t *p = NULL;
    history_t *c = *history;
    history_t *n;

    while (c != NULL) {
        n = c->next;
        c->next = p;
        p = c;
        c = n;
    }
    return p;
}

static history_t *get_history_aux(history_t **history, char *buf)
{
    char **tmp;
    char **tab = sep_str(buf, 1, "\n");

    for (int i = 0; i < my_strlen_array(tab); i++) {
        tmp = sep_str(tab[i], 1, " ");
        *history = create_new_history_node(convert_str_in_int(tmp[0]), tmp[1],
        parse_str(tab[i], 1 + my_strlen(tmp[0]) + 1 + my_strlen(tmp[1]) + 1,
        my_strlen(tab[i])), *history);
        free_word_array(tmp);
    }
    free_word_array(tab);
    return *history;
}

history_t *get_history(history_t **history)
{
    struct stat st;
    int fd = open(".history", O_RDONLY);
    char *buf;

    if (fd == -1) {
        mini_printf("Can't find '.history' file.\n");
        return NULL;
    }
    if (stat(".history", &st) == -1 || st.st_size == 0 || st.st_size == 1) {
        close(fd);
        return NULL;
    }
    buf = malloc(sizeof(char) * (st.st_size + 1));
    read(fd, buf, st.st_size);
    buf[st.st_size] = '\0';
    *history = get_history_aux(history, buf);
    free(buf);
    close(fd);
    return rev_history(history);
}

void print_history(int fd, history_t **history)
{
    history_t *node = *history;

    while (node != NULL) {
        mini_fdprintf(fd, "\t%d\t%s\t%s\n", node->id, node->ctime,
        node->command);
        node = node->next;
    }
}

static void save_history(history_t **history)
{
    int fd = open(".history", O_RDWR | O_TRUNC);

    if (fd == -1) {
        mini_printf("Can't find '.history' file.\n");
        return;
    }
    print_history(fd, history);
    close(fd);
}

void destroy_history(history_t **history)
{
    history_t *node = *history;
    history_t *tmp = NULL;

    save_history(history);
    while (node != NULL) {
        tmp = node;
        node = node->next;
        free(tmp->ctime);
        free(tmp);
    }
}

void add_history(history_t **history, char *command)
{
    history_t *node = *history;
    history_t *tmp;
    time_t mytime = time(NULL);

    if (my_strcmp(node->command, command) == 0) {
        *history = node->next;
        return;
    }
    while (node->next != NULL) {
        if (my_strcmp(node->next->command, command) == 0) {
            tmp = node->next;
            node->next = node->next->next;
            free(tmp->ctime);
            free(tmp);
        }
        node = node->next;
    }
    node->next = create_new_history_node(node->id, ctime(&mytime),
    command, NULL);
}
