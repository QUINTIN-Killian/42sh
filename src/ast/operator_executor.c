/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** operator_executor.c
*/

#include <unistd.h>
#include <fcntl.h>
#include "../../include/mysh.h"
#include "../../include/my.h"

int execute_normal(ast_node_t *node, shell_t *shell)
{
    int pid;
    char **args = sep_str(node->value, 2, " ", "\t");

    if (explore_var_env(args, shell) || is_exit(args, shell)) {
        free_word_array(args);
        return 0;
    }
    pid = fork();
    if (pid == 0){
        my_exec(args, shell);

    } else
        print_res(pid, shell);
    free_word_array(args);
    return pid;
}

int execute_redirect(ast_node_t *node, shell_t *shell)
{
    int fd = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char **args = sep_str(node->left->value, 2, " ", "\t");
    int pid;

    if (fd == -1)
        return print_execve_error(args[0], "Permission denied.\n");
    if (explore_var_env(args, shell) || is_exit(args, shell)) {
        free_word_array(args);
        return 0;
    }
    pid = fork();
    if (pid == 0){
        dup2(fd, 1);
        close(fd);
        my_exec(args, shell);
    } else
        print_res(pid, shell);
    free_word_array(args);
    return pid;
}

int execute_pipe(ast_node_t *node, shell_t *shell)
{
    char **args = sep_str(node->value, 2, " ", "\t");
    int pid;

    if (explore_var_env(args, shell) || is_exit(args, shell)) {
        free_word_array(args);
        return 0;
    }
    pid = fork();
    if (pid == 0){
        close(shell->pipefd[0]);
        dup2(shell->pipefd[1], STDOUT_FILENO);
        close(shell->pipefd[1]);
        my_exec(args, shell);
    } else
        print_res(pid, shell);
    free_word_array(args);
    return pid;
}

int execute_append(ast_node_t *node, shell_t *shell)
{
    int fd = open(node->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
    char **args = sep_str(node->left->value, 2, " ", "\t");
    int pid;

    if (fd == -1)
        return print_execve_error(args[0], "Permission denied.\n");
    if (explore_var_env(args, shell) || is_exit(args, shell)) {
        free_word_array(args);
        return 0;
    }
    pid = fork();
    if (pid == 0){
        dup2(fd, 1);
        close(fd);
        my_exec(args, shell);
    } else
        print_res(pid, shell);
    free_word_array(args);
    return pid;
}

int execute_input(ast_node_t *node, shell_t *shell)
{
    int fd = open(node->right->value, O_RDONLY);
    char **args = sep_str(node->left->value, 2, " ", "\t");
    int pid;

    if (fd == -1)
        return print_execve_error(args[0], "No such file or directory.\n");
    if (explore_var_env(args, shell) || is_exit(args, shell)) {
        free_word_array(args);
        return 0;
    }
    pid = fork();
    if (pid == 0){
        dup2(fd, 0);
        close(fd);
        my_exec(args, shell);
    } else
        print_res(pid, shell);
    free_word_array(args);
    return pid;
}
