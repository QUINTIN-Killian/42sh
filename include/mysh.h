/*
** EPITECH PROJECT, 2024
** mini_shell1
** File description:
** mysh header
** mysh
*/

#ifndef MYSH_H_
    #define MYSH_H_
    #include "my.h"
    #include <time.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <dirent.h>

typedef struct env_s {
    char *env;
    struct env_s *next;
} env_t;

typedef struct history_s {
    int id;
    char *ctime;
    char *command;
    struct history_s *next;
} history_t;

typedef struct shell_s {
    int exit;
    int ac;
    char **av;
    env_t *head;
    history_t *history;
    int last_return;
    char **separators;
    int ind;
    int pipefd[2];
    int fd_input;
    char *input;
    char **command_array;
    char **command_array_sep;
} shell_t;

//my_scanf.c :
char *my_scanf(void);

//exit.c :
int error_handling_exit(shell_t *shell);

//history.c :
history_t *get_history(history_t **history);
void print_history(int fd, history_t **history);
void destroy_history(history_t **history);
void add_history(history_t **history, char *command);
int history(shell_t *shell);

//var_env.c
int explore_var_env(shell_t *shell);

//my_env.c :
env_t *add_env(char *env);
int my_env(shell_t *shell);
int del_env(shell_t *shell, char *key);
int change_var_env(shell_t *shell, char *key, char *new_env);

//my_cd.c :
int my_cd(shell_t *shell);

//functions.c :
char *get_env_value(shell_t *shell, char *key);
char **parse_env_value(char const *str);
char **convert_linked_list_in_word_array(shell_t *shell);
int count_occ_motif(char *str, char *motif);

//interpreter.c :
void separator_interpreter1(shell_t *shell, int i);
void command_interpreter(shell_t *shell, int i);

//command_separators.c :
char **realloc_tab_plus_one(char **tab);
void get_command_separators(shell_t *shell, char *command);

//error_handling_command.c :
int error_handling_input(shell_t *shell);

//right_redirections.c :
void double_right_redirection(shell_t *shell, int i);
void simple_right_redirection(shell_t *shell);

//shell.c :
int error_handling_exit(shell_t *shell);
int shell_interface(shell_t *shell);

//my_setenv.c :
int my_setenv(shell_t *shell);

//my_unsetenv.c :
int my_unsetenv(shell_t *shell);

//caller.c :
void call_bin(shell_t *shell);

#endif
