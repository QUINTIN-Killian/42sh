/*
** EPITECH PROJECT, 2024
** mini_shell2
** File description:
** right redirections
** right_redirections
*/

#include "../include/mysh.h"

static bool is_same_file(shell_t *shell, char *filename,
    char **command_array_sep, int ind)
{
    char **tmp;
    struct stat st;

    if (ind <= 0 || stat(filename, &st) == -1 || st.st_size == 0)
        return false;
    tmp = separate_words_on_spaces(command_array_sep[ind - 1]);
    for (int i = my_strlen_array(tmp) - 1; i >= 0; i--) {
        if (my_strcmp(tmp[i], filename) == 0) {
            free_word_array(tmp);
            shell->last_return = 1;
            return true;
        }
    }
    free_word_array(tmp);
    return false;
}

static void error_same_file(char **command_array_sep, int i, char **filename)
{
    char **tmp = separate_words_on_spaces(command_array_sep[i - 1]);

    mini_printf("%s: %s: input file is output file\n",
    tmp[0], filename[0]);
    free_word_array(tmp);
}

void double_right_redirection(shell_t *shell, char **command_array_sep, int i,
    char **filename)
{
    int redirection_fd;
    char buf;
    struct stat st;

    shell->last_return = 0;
    if (shell->fd_input == -1 || filename == NULL || filename[0] == NULL)
        return;
    if (stat(filename[0], &st) == 0) {
        if (is_same_file(shell, filename[0], command_array_sep, i))
            return error_same_file(command_array_sep, i, filename);
        redirection_fd = open(filename[0], O_WRONLY | O_APPEND);
    } else
        redirection_fd = open(filename[0], O_CREAT | O_WRONLY);
    if (redirection_fd == -1)
        return;
    while (read(shell->fd_input, &buf, 1) > 0)
        write(redirection_fd, &buf, 1);
    close(redirection_fd);
}

void simple_right_redirection(shell_t *shell, char **filename)
{
    int redirection_fd;
    char buf;
    struct stat st;

    shell->last_return = 0;
    if (shell->fd_input == -1 || filename == NULL || filename[0] == NULL)
        return;
    if (stat(filename[0], &st) == 0)
        redirection_fd = open(filename[0], O_WRONLY | O_TRUNC);
    else
        redirection_fd = open(filename[0], O_CREAT | O_WRONLY);
    if (redirection_fd == -1)
        return;
    while (read(shell->fd_input, &buf, 1) > 0)
        write(redirection_fd, &buf, 1);
    close(redirection_fd);
}
