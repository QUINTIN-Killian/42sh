/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** cd builtin
** cd
*/

#include "../include/mysh.h"

static int error_handling_cd(shell_t *shell)
{
    if (my_strlen_array(shell->command_array) == 2 &&
    (my_strcmp(shell->command_array[1], "-") == 0 ||
    my_strcmp(shell->command_array[1], "~") == 0))
        return 0;
    if (my_strlen_array(shell->command_array) > 2) {
        mini_fdprintf(shell->pipefd[1], "cd: Too many arguments.\n");
        return 1;
    }
    return 0;
}

static int cd_home_and_minus(shell_t *shell, char *tmp, char *old_pwd)
{
    int ans;
    char *buffer_new = NULL;
    char *new_pwd;

    ans = chdir(tmp);
    free(tmp);
    shell->last_return = 0;
    buffer_new = getcwd(NULL, 0);
    new_pwd = concat_2_str("PWD=", buffer_new);
    free(buffer_new);
    change_var_env(shell, "PWD", new_pwd);
    change_var_env(shell, "OLDPWD", old_pwd);
    return ans;
}

int cd_home(shell_t *shell)
{
    char *tmp = get_env_value(shell, "HOME");
    char *buffer_old = getcwd(NULL, 0);
    char *old_pwd = concat_2_str("OLDPWD=", buffer_old);

    free(buffer_old);
    if (tmp == NULL) {
        shell->last_return = 1;
        return -1;
    }
    return cd_home_and_minus(shell, tmp, old_pwd);
}

int cd_minus(shell_t *shell)
{
    char *tmp = get_env_value(shell, "OLDPWD");
    char *buffer_old = getcwd(NULL, 0);
    char *old_pwd = concat_2_str("OLDPWD=", buffer_old);

    free(buffer_old);
    if (tmp == NULL) {
        shell->last_return = 1;
        return -1;
    }
    return cd_home_and_minus(shell, tmp, old_pwd);
}

static void my_cd_error(shell_t *shell)
{
    mini_fdprintf(shell->pipefd[1],
    "%s: %s.\n", shell->command_array[1], strerror(errno));
    shell->last_return = 1;
}

static int my_cd_aux(shell_t *shell)
{
    if (error_handling_cd(shell)) {
        shell->last_return = 1;
        return 1;
    }
    if (my_strlen_array(shell->command_array) == 1 ||
    my_strcmp(shell->command_array[1], "~") == 0)
        return cd_home(shell);
    if (my_strcmp(shell->command_array[1], "-") == 0)
        return cd_minus(shell);
    return -2;
}

static int cd_switch_env(shell_t *shell, int ans, char *old_pwd)
{
    char *buffer_new = NULL;
    char *new_pwd;

    if (ans != 0) {
        my_cd_error(shell);
        free(old_pwd);
    } else {
        buffer_new = getcwd(NULL, 0);
        new_pwd = concat_2_str("PWD=", buffer_new);
        free(buffer_new);
        change_var_env(shell, "PWD", new_pwd);
        change_var_env(shell, "OLDPWD", old_pwd);
        shell->last_return = 0;
    }
    return 0;
}

int my_cd(shell_t *shell)
{
    int ans;
    char *buffer_old = NULL;
    char *old_pwd;

    if (my_cd_aux(shell) != -2)
        return 0;
    buffer_old = getcwd(NULL, 0);
    old_pwd = concat_2_str("OLDPWD=", buffer_old);
    free(buffer_old);
    ans = chdir(shell->command_array[1]);
    cd_switch_env(shell, ans, old_pwd);
    return ans;
}
