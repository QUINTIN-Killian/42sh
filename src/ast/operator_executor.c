/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** operator_executor.c
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../include/mysh.h"
#include "../../include/my.h"

static void print_res(pid_t child, char *program_name, shell_t *shell)
{
    int status;

    waitpid(child, &status, 0);
    if (WIFSIGNALED(status)) {
        status = WTERMSIG(status);
        mini_fdprintf(0, "%s\n", strsignal(status));
        if (WCOREDUMP(status))
            shell->last_return = 128 + status;
        else
            shell->last_return = 1;
    }
}

int execute_normal(ast_node *node, shell_t *shell)
{
    int pid;
    char **args = sep_str(node->value, 2, " ", "\t");

    if (is_builtin(args, shell) == 1){
        free_word_array(args);
        return(0);
    }
    pid = fork();
    if (pid == 0){
        if (execvp(args[0], args) == -1)
            mini_fdprintf(2, "%s: Permission denied.\n", args[0]);
    } else
        print_res(pid, args[0], shell);
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
    if (is_builtin(args, shell) == 1){
        free_word_array(args);
        return(0);
    }
    pid = fork();
    if (pid == 0){
        dup2(fd, 1);
        close(fd);
        if (execvp(args[0], args) == -1)
            mini_fdprintf(2, "%s: Permission denied.\n", args[0]);
    } else
        print_res(pid, args[0], shell);
    free_word_array(args);
    return pid;
}

int execute_pipe(ast_node *node, shell_t *shell)
{
    char **args = sep_str(node->value, 2, " ", "\t");
    int pid;

    if (is_builtin(args, shell) == 1){
        free_word_array(args);
        return(0);
    }
    pid = fork();
    if (pid == 0){
        close(shell->pipefd[0]);
        dup2(shell->pipefd[1], STDOUT_FILENO);
        close(shell->pipefd[1]);
        if (execvp(args[0], args) == -1)
            mini_fdprintf(2, "%s: Permission denied.\n", args[0]);
    } else
        print_res(pid, args[0], shell);
    free_word_array(args);
    return pid;
}


int execute_append(ast_node *node, shell_t *shell)
{
    int fd = open(node->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
    char **args = sep_str(node->left->value, 2, " ", "\t");
    int pid;

    if (fd == -1)
        return print_execve_error(args[0], "Permission denied.\n");
    if (is_builtin(args, shell) == 1){
        free_word_array(args);
        return(0);
    }
    pid = fork();
    if (pid == 0){
        dup2(fd, 1);
        close(fd);
        if (execvp(args[0], args) == -1)
            mini_fdprintf(2, "%s: Permission denied.\n", args[0]);
    } else
        print_res(pid, args[0], shell);
    free_word_array(args);
    return pid;
}

int execute_input(ast_node *node, shell_t *shell)
{
    int fd = open(node->right->value, O_RDONLY);
    char **args = sep_str(node->left->value, 2, " ", "\t");
    int pid;

    if (fd == -1)
        return print_execve_error(args[0], "No such file or directory.\n");
    if (is_builtin(args, shell) == 1){
        free_word_array(args);
        return(0);
    }
    pid = fork();
    if (pid == 0){
        dup2(fd, 0);
        close(fd);
        if (execvp(args[0], args) == -1)
            mini_fdprintf(2, "%s: Permission denied.\n", args[0]);
    } else
        print_res(pid, args[0], shell);
    free_word_array(args);
    return pid;
}
