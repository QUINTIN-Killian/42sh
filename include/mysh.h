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

typedef struct env_s {
    char *env;
    struct env_s *next;
} env_t;

typedef struct shell_s {
    int exit;
    int ac;
    char **av;
    env_t *head;
    int last_return;
    char **separators;
    int ind;
    int pipefd[2];
    int fd_input;
} shell_t;

//main.c :
void print_word_array(char **word_array);

//my_scanf.c :
char *my_scanf(void);

//my_env.c :
env_t *add_env(char *env);
int my_env(char **command_array, shell_t *shell);
int del_env(shell_t *shell, char *key);
int change_var_env(shell_t *shell, char *key, char *new_env);

//my_cd.c :
int my_cd(char **command_array, shell_t *shell);

//functions.c :
char *get_env_value(shell_t *shell, char *key);
char **parse_env_value(char const *str);
char **convert_linked_list_in_word_array(shell_t *shell);
int count_occ_motif(char *str, char *motif);

//interpreter.c :
void separator_interpreter1(char **command_array, shell_t *shell,
    char **command_array_sep, int i);
void command_interpreter(char **command_array, shell_t *shell,
    char **command_array_sep, int i);

//command_separators.c :
char **realloc_tab_plus_one(char **tab);
void get_command_separators(shell_t *shell, char *command);

//error_handling_command.c :
bool error_handling_command(shell_t *shell, char *input);

//right_redirections.c :
void double_right_redirection(shell_t *shell, char **command_array_sep, int i,
    char **filename);
void simple_right_redirection(shell_t *shell, char **filename);

//shell.c :
int error_handling_exit(char **command_array, shell_t *shell);
int shell_interface(shell_t *shell);

//my_setenv.c :
int my_setenv(char **command_array, shell_t *shell);

//my_unsetenv.c :
int my_unsetenv(char **command_array, shell_t *shell);

//caller.c :
void call_bin(char **command_array, shell_t *shell);

// ast
typedef enum {
    COMMAND,
    PIPE,
    SEMICOLON,
    REDIRECTION_RIGTH,
    REDIRECTION_LEFT,
    DOUBLE_LEFT,
    DOUBLE_RIGHT
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

typedef struct ast_node {
    TokenType type;
    char *value;
    struct ast_node *left;
    struct ast_node *right;
} ast_node;

void ast_parse_semicolon(ast_node *node);
void ast_parse_pipe(ast_node *node);
void ast_parse_redirection_rigth(ast_node *node);
void ast_parse_redirection_left(ast_node *node);
void ast_parse(ast_node *node, char *pat);

ast_node *create_ast_node(TokenType type, char *value);
void free_ast_node(ast_node *node);
ast_node *build_ast(char *input);
int execute_ast_node(ast_node *node, char ***env);

#endif
