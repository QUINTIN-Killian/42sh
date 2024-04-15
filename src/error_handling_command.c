/*
** EPITECH PROJECT, 2024
** mini_shell2
** File description:
** error handling command management
** error_handling_command
*/

#include "../include/mysh.h"

static bool space_checker(char **tmp)
{
    char **checker;

    for (int i = 0; i < my_strlen_array(tmp); i++) {
        checker = sep_str(tmp[i], 2, "\t", " ");
        if (checker == NULL || checker[0] == NULL) {
            free_word_array(checker);
            return true;
        }
        free_word_array(checker);
    }
    return false;
}

static bool print_error(char **tmp, char **sep, int i, int occ)
{
    if (space_checker(tmp) || occ >= my_strlen_array(tmp)) {
        free_word_array(tmp);
        my_fdputstr(2, "Missing name for redirect.\n");
        return true;
    }
    if (my_strlen_array(tmp) > 2 && sep[i][0] == '>') {
        free_word_array(tmp);
        my_fdputstr(2, "Ambiguous output redirect.\n");
        return true;
    }
    if (my_strlen_array(tmp) > 2 && sep[i][0] == '<') {
        free_word_array(tmp);
        my_fdputstr(2, "Ambiguous input redirect.\n");
        return true;
    }
    return false;
}

static bool pipe_error(char *command)
{
    char **tmp = sep_str(command, 1, "|");
    int occ = count_occ_motif(command, "|");

    if (space_checker(tmp) || occ >= my_strlen_array(tmp)) {
        free_word_array(tmp);
        my_fdputstr(2, "Invalid null command.\n");
        return true;
    }
    free_word_array(tmp);
    return false;
}

static bool analyse_command(char *command, char **sep)
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
            return false;
        free_word_array(tmp);
    }
    return !pipe_error(command);
}

bool error_handling_command(shell_t *shell, char *input)
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
            return true;
        }
    }
    free_word_array(commands);
    free_word_array(sep);
    return false;
}
