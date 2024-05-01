/*
** EPITECH PROJECT, 2024
** 42sh-private
** File description:
** history_getter
*/

#include "../../include/mysh.h"

static void forward_ind(int *ind, char **input)
{
    if (*ind < my_strlen(*input) && (*input)[*ind] == '-')
        *ind += 1;
    while (*ind < my_strlen(*input) && (((*input)[*ind] >= '0' &&
    (*input)[*ind] <= '9') || ((*input)[*ind] >= 'A' && (*input)[*ind]
    <= 'Z') || ((*input)[*ind] >= 'a' && (*input)[*ind] <= 'z')))
        *ind += 1;
}

static void set_new_input(char **input, char **reimplace, int i,
    int ind)
{
    char *part1 = parse_str(*input, 0, i);
    char *part2 = parse_str(*input, ind, my_strlen(*input));

    free(*input);
    *input = concat_str(3, part1, *reimplace, part2);
    if (part1 != NULL)
        free(part1);
    if (part2 != NULL)
        free(part2);
    free(*reimplace);
}

static int exit_special_cases(char **ref, char **input, int ind, int *i)
{
    if (ind == *i + 1)
        return 1;
    *ref = parse_str(*input, *i, ind);
    if (*ref == NULL)
        return 1;
    if (my_strcmp(*ref, "!-") == 0) {
        free(*ref);
        return 1;
    }
    return 0;
}

static int reimplace_history_getter_aux(shell_t *shell, char **input, int *i,
    int *change)
{
    int ind;
    char *ref;
    char *reimplace;

    if ((*input)[*i] == '!') {
        ind = *i + 1;
        forward_ind(&ind, input);
        if (exit_special_cases(&ref, input, ind, i))
            return 0;
        *change = 1;
        reimplace = my_strdup(get_history_id(&shell->history, ref));
        free(ref);
        if (reimplace == NULL)
            return 1;
        set_new_input(input, &reimplace, *i, ind);
        *i -= 1;
    }
    return 0;
}

int reimplace_history_getter(shell_t *shell, char **input)
{
    int change = 0;

    for (int i = 0; i < my_strlen(*input); i++)
        if (reimplace_history_getter_aux(shell, input, &i, &change))
            return 1;
    if (change)
        mini_printf("%s\n", *input);
    return 0;
}
