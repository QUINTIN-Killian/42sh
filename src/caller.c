/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** call binaries and other
** caller
*/

#include "../include/mysh.h"

static void call_bin_error(int status, shell_t *shell)
{
    if (WIFEXITED(status)) {
        shell->last_return = WEXITSTATUS(status);
        return;
    }
    if (WIFSIGNALED(status)) {
        mini_printf("%s\n", strsignal(WTERMSIG(status)));
        shell->last_return = status;
        return;
    }
    if (WIFSTOPPED(status)) {
        mini_printf("%s\n", strsignal(WSTOPSIG(status)));
        shell->last_return = status;
        return;
    }
    if (errno != 0) {
        mini_printf("%s\n", strerror(errno));
        shell->last_return = status;
    }
}

static void is_dir(shell_t *shell, char *command)
{
    DIR *dir = opendir(command);

    if (dir != NULL) {
        mini_fdprintf(shell->pipefd[1],
        "%s: Permission denied.\n", command);
        closedir(dir);
        exit(1);
    }
}

static int call_not_bin(shell_t *shell, char **environment)
{
    char *command = shell->command_array[0];
    int ret = execve(command, shell->command_array, environment);

    free_word_array(environment);
    if (ret == -1) {
        if (errno == 8) {
            mini_fdprintf(shell->pipefd[1],
            "%s: Exec format error. Wrong Architecture.\n",
            shell->command_array[0]);
            exit(1);
        }
        is_dir(shell, command);
        mini_fdprintf(shell->pipefd[1],
        "%s: Command not found.\n", shell->command_array[0]);
        exit(1);
    }
    exit(ret);
}

static int child_pid_actions(char **calls, shell_t *shell)
{
    char *command;
    int ret;
    char **environment = convert_linked_list_in_word_array(shell);

    close(shell->pipefd[0]);
    if (shell->ind < my_strlen_array(shell->separators))
        dup2(shell->pipefd[1], STDOUT_FILENO);
    if (shell->fd_input != -1)
        dup2(shell->fd_input, STDIN_FILENO);
    for (int i = 0; i < my_strlen_array(calls); i++) {
        command = concat_str(3, calls[i], "/", shell->command_array[0]);
        ret = execve(command, shell->command_array, environment);
        free(command);
        if (ret != -1) {
            free_word_array(environment);
            exit(ret);
        }
    }
    call_not_bin(shell, environment);
    return 1;
}

void call_bin(shell_t *shell)
{
    char *path = get_env_value(shell, "PATH");
    char **calls;
    int status = 0;
    int child_pid;

    if (path == NULL)
        return;
    calls = parse_env_value(path);
    free(path);
    child_pid = fork();
    if (child_pid == 0) {
        child_pid_actions(calls, shell);
    } else {
        if (shell->separators == NULL ||
        shell->ind >= my_strlen_array(shell->separators))
            waitpid(child_pid, &status, WUNTRACED);
        close(shell->pipefd[1]);
    }
    free_word_array(calls);
    call_bin_error(status, shell);
}
