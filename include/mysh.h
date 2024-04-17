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
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <dirent.h>
    #include <time.h>

    #define BUILTIN_ERROR (-1)
    #define BUILTIN_FINE (-2)
    #define BUILTIN_NO_F (-3)

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

typedef enum {
    COMMAND,
    PIPE,
    SEMICOLON,
    REDIRECTION_RIGTH,
    REDIRECTION_LEFT,
    DOUBLE_LEFT,
    DOUBLE_RIGHT
} TokenType_t;

typedef struct ast_node_s {
    TokenType_t type;
    char *value;
    struct ast_node_s *left;
    struct ast_node_s *right;
} ast_node_t;

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
    ast_node_t *ast;
} shell_t;

//my_scanf.c :
char *my_scanf(void);

//my_env.c :
env_t *add_env(char *env);
int my_env(char **command_array, shell_t *shell);
int del_env(shell_t *shell, char *key);
int change_var_env(shell_t *shell, char *key, char *new_env);

//history.c :
history_t *get_history(history_t **history);
void print_history(int fd, history_t **history, int nb_print);
void destroy_history(history_t **history);
history_t *create_new_history_node(int id, char *ctime, char *command,
    history_t *next);

//history2.c :
int get_len_history(history_t **history);
void add_history(history_t **history, char *command);
int history(char **command_array, shell_t *shell);

//my_cd.c :
int my_cd(char **command_array, shell_t *shell);

//var_env.c :
int explore_var_env(char **command_array, shell_t *shell);

//functions.c :
char *get_env_value(shell_t *shell, char *key);
char **convert_linked_list_in_word_array(shell_t *shell);
int count_occ_motif(char *str, char *motif);

//command_separators.c :
char **realloc_tab_plus_one(char **tab);
void get_command_separators(shell_t *shell, char *command);

//error_handling_command.c :
int error_handling_input(shell_t *shell, char *input);

//exit.c :
int my_exit(char **command_array, shell_t *shell);

//shell.c :
int my_exit(char **command_array, shell_t *shell);
int shell_interface(shell_t *shell);

//my_setenv.c :
int my_setenv(char **command_array, shell_t *shell);

//my_unsetenv.c :
int my_unsetenv(char **command_array, shell_t *shell);

//ast
void ast_parse(ast_node_t *node, char *pat);

ast_node_t *create_ast_node(TokenType_t type, char *value);
void free_ast_node(ast_node_t *node);
ast_node_t *build_ast(char *input);
int execute_ast_node(ast_node_t *node, shell_t *shell);

//operator_executor2.c :
void print_res(pid_t child, shell_t *shell);

int print_execve_error(char *command, char *error);

//executor
int execute_normal(ast_node_t *node, shell_t *shell);
int execute_redirect(ast_node_t *node, shell_t *shell);
int execute_input(ast_node_t *node, shell_t *shell);
int execute_append(ast_node_t *node, shell_t *shell);
int execute_input_here(ast_node_t *node, shell_t *shell);
int execute_pipe(ast_node_t *node, shell_t *shell);

int is_builtin(char **args, shell_t *shell);
void my_exec(char **args, shell_t *shell);
int is_exit(char **args, shell_t *shell);
#endif
