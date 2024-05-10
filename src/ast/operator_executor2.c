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

void print_res(pid_t child, shell_t *shell)
{
    int status;

    waitpid(child, &status, WUNTRACED);
    if (WIFEXITED(status)) {
        shell->last_return = WEXITSTATUS(status);
        return;
    } else if (WIFSIGNALED(status)) {
        mini_printf("%s\n", strsignal(WTERMSIG(status)));
        shell->last_return = status;
        return;
    }
    if (WIFSTOPPED(status)) {
        mini_printf("%s\n", strsignal(WSTOPSIG(status)));
        shell->last_return = status;
    } else if (errno != 0) {
        mini_printf("%s\n", strerror(errno));
        shell->last_return = status;
    }
}

static void exec_dir(char **args)
{
    DIR *dir = opendir(args[0]);

    if (dir != NULL) {
        mini_fdprintf(2, "%s: Permission denied.\n", args[0]);
        closedir(dir);
        exit(1);
    }
}

void my_exec(char **args, shell_t *shell)
{
    if (is_builtin(args, shell) || args == NULL){
        exit(0);
        return;
    }
    if (execvp(args[0], args) == -1){
        exec_dir(args);
        mini_fdprintf(2, "%s: Command not found.\n", args[0]);
        exit(1);
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

    if (handle_aliases(&args, shell))
        return 1;
    res = must_exec(args, shell, fd);
    if (res != 1)
        return res;
    pid = fork();
    if (pid == 0){
        close(fd[0]);
        input_here_loop(fd, node->right->value);
        close(fd[1]);
        my_exec(args, shell);
    } else
        print_res(pid, shell);
    free_word_array(args);
    return pid;
}
