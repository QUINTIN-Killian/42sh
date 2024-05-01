/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-42sh-florian.reynaud
** File description:
** config.c
*/

#include "../include/mysh.h"

#include <stdbool.h>
#include <stdio.h>

const char *config_files[] = {
    ".42shrc",
};

bool is_file(char *path)
{
    struct stat statbuf;

    return stat(path, &statbuf) == 0 ? true : false;
}

static void exec_line(shell_t *shell, char *file_path, char *line,
    uint32_t nline)
{
    shell->ast = build_ast(line);
    execute_ast_node(shell->ast, shell);
    free_ast_node(shell->ast);
    if (shell->last_return != 0) {
        fprintf(stderr, "Error in config file '%s', line %u\n'",
        file_path, nline);
    }
}

static void execute_file(shell_t *shell, char *file_path)
{
    FILE *file = fopen(file_path, "r");
    uint32_t nline = 0;
    char *line = NULL;
    size_t _;

    while (getline(&line, &_, file) != -1) {
        line[strlen(line) - 1] = '\0';
        if (strlen(line) == 0) {
            nline++;
            continue;
        }
        exec_line(shell, file_path, line, nline);
        nline++;
    }
    free(line);
    fclose(file);
}

void source_config(shell_t *shell)
{
    for (int i = 0; i < ARR_SIZE(config_files); i++) {
        if (!is_file((char *)config_files[i])) {
            fprintf(stderr, "Unknown config file '%s'\n", config_files[i]);
            continue;
        }
        execute_file(shell, (char *)config_files[i]);
    }
}
