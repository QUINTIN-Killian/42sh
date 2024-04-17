/*
** EPITECH PROJECT, 2024
** 42sh-private
** File description:
** operator_executor2
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
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

static void input_here_loop(int fd[2], char *filename)
{
    char *line = NULL;
    size_t len = 0;

    while (1) {
        my_putstr("? ");
        if (getline(&line, &len, stdin) == -1)
            break;
        if (my_strncmp(line, filename, my_strlen(filename) - 1) == 0)
            break;
        write(fd[1], line, my_strlen(line));
    }
}

static int must_exec(char **args, shell_t *shell, int *fd)
{
    if (pipe(fd) == -1)
        return BUILTIN_ERROR;
    if (is_builtin(args, shell) == 1){
        free_word_array(args);
        return (0);
    }
    return (1);
}

int execute_input_here(ast_node_t *node, shell_t *shell)
{
    char **args = sep_str(node->left->value, 2, " ", "\t");
    int fd[2];
    int pid;
    int res;

    res = must_exec(args, shell, fd);
    if (res != 1)
        return res;
    pid = fork();
    if (pid == 0){
        close(fd[0]);
        input_here_loop(fd, node->right->value);
        close(fd[1]);
        if (execvp(args[0], args) == -1)
            mini_fdprintf(2, "%s: Permission denied.\n", args[0]);
    } else
        print_res(pid, args[0], shell);
    free_word_array(args);
    return pid;
}
