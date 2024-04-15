/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** operator_executor.c
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../include/mysh.h"
#include "../../include/my.h"

int execute_normal(ast_node *node, shell_t *shell)
{
    int pid = fork();
    char **args = sep_str(node->value, 2, " ", "\t");

    if (pid == BUILTIN_ERROR)
        return BUILTIN_ERROR;
    if (pid == 0) {
        my_execve(args[0], args, shell);
        exit(0);
    }
    free_word_array(args);
    return pid;
}

int execute_redirect(ast_node *node, shell_t *shell)
{
    int fd = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char **args = sep_str(node->left->value, 2, " ", "\t");
    int pid;

    if (fd == -1)
        return print_execve_error(args[0], "Permission denied.\n");
    pid = fork();
    if (pid == BUILTIN_ERROR)
        return BUILTIN_ERROR;
    if (pid == 0) {
        dup2(fd, 1);
        close(fd);
        my_execve(args[0], args, shell);
        exit(0);
    }
    return pid;
}

int execute_append(ast_node *node, shell_t *shell)
{
    int fd = open(node->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
    char **args = sep_str(node->left->value, 2, " ", "\t");
    int pid;

    if (fd == -1)
        return print_execve_error(args[0], "Permission denied.\n");
    pid = fork();
    if (pid == BUILTIN_ERROR)
        return BUILTIN_ERROR;
    if (pid == 0) {
        dup2(fd, 1);
        close(fd);
        my_execve(args[0], args, shell);
        exit(0);
    }
    return pid;
}

int execute_input(ast_node *node, shell_t *shell)
{
    int fd = open(node->right->value, O_RDONLY);
    char **args = sep_str(node->left->value, 2, " ", "\t");
    int pid;

    if (fd == -1)
        return print_execve_error(args[0], "No such file or directory.\n");
    pid = fork();
    if (pid == BUILTIN_ERROR)
        return BUILTIN_ERROR;
    if (pid == 0) {
        dup2(fd, 0);
        close(fd);
        my_execve(args[0], args, shell);
        exit(0);
    }
    return pid;
}

static void input_here_loop(int fd[2], char *filename)
{
    char *line = NULL;
    size_t len = 0;

    while (1) {
        my_putstr("? ");
        if (getline(&line, &len, stdin) == -1)
            break;
        if (my_strcmp(line, filename) == 0)
            break;
        write(fd[1], line, my_strlen(line));
    }
}

int execute_input_here(ast_node *node, shell_t *shell)
{
    char **args = sep_str(node->left->value, 2, " ", "\t");
    int fd[2];
    int pid;

    if (pipe(fd) == -1)
        return BUILTIN_ERROR;
    pid = fork();
    if (pid == BUILTIN_ERROR)
        return BUILTIN_ERROR;
    if (pid == 0) {
        close(fd[0]);
        input_here_loop(fd, node->right->value);
        close(fd[1]);
        my_execve(args[0], args, shell);
        exit(0);
    }
    return pid;
}
