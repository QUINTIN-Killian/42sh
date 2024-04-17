/*
** EPITECH PROJECT, 2024
** mini_shell2
** File description:
** error handling command management
** error_handling_command
*/

#include "../include/mysh.h"

static int space_checker(char **tmp)
{
    char **checker;

    for (int i = 0; i < my_strlen_array(tmp); i++) {
        checker = sep_str(tmp[i], 2, "\t", " ");
        if (checker == NULL || checker[0] == NULL) {
            free_word_array(checker);
            return 1;
        }
        free_word_array(checker);
    }
    return 0;
}

static int print_error(char **tmp, char **sep, int i, int occ)
{
    if (space_checker(tmp) || occ >= my_strlen_array(tmp)) {
        free_word_array(tmp);
        my_fdputstr(2, "Missing name for redirect.\n");
        return 1;
    }
    if (my_strlen_array(tmp) > 2 && sep[i][0] == '>') {
        free_word_array(tmp);
        my_fdputstr(2, "Ambiguous output redirect.\n");
        return 1;
    }
    if (my_strlen_array(tmp) > 2 && sep[i][0] == '<') {
        free_word_array(tmp);
        my_fdputstr(2, "Ambiguous input redirect.\n");
        return 1;
    }
    return 0;
}

static int pipe_error(char *command)
{
    char **tmp = sep_str(command, 1, "|");
    int occ = count_occ_motif(command, "|");

    if (space_checker(tmp) || occ >= my_strlen_array(tmp)) {
        free_word_array(tmp);
        my_fdputstr(2, "Invalid null command.\n");
        return 1;
    }
    free_word_array(tmp);
    return 0;
}

static int analyse_command(char *command, char **sep)
{
    int occ;
    char **tmp;

    for (int i = 0; i < 4; i++) {
        tmp = sep_str(command, 1, sep[i]);
        occ = count_occ_motif(command, sep[i]);
        if (my_strcmp(sep[i], ">") == 0)
            occ = occ - (count_occ_motif(command, ">>") * 2);
        if (my_strcmp(sep[i], "<") == 0)
            occ = occ - (count_occ_motif(command, "<<") * 2);
        if (print_error(tmp, sep, i, occ))
            return 0;
        free_word_array(tmp);
    }
    return !pipe_error(command);
}

int error_handling_input(shell_t *shell, char *input)
{
    char **commands = sep_str(input, 1, ";");
    char **sep = malloc(sizeof(char *) * 5);

    sep[0] = my_strdup(">");
    sep[1] = my_strdup(">>");
    sep[2] = my_strdup("<");
    sep[3] = my_strdup("<<");
    sep[4] = NULL;
    for (int i = 0; i < my_strlen_array(commands); i++) {
        if (!analyse_command(commands[i], sep)) {
            shell->last_return = 1;
            free_word_array(commands);
            free_word_array(sep);
            return 1;
        }
    }
    free_word_array(commands);
    free_word_array(sep);
    return 0;
}
