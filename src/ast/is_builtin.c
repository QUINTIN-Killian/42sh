/*
** EPITECH PROJECT, 2024
** 42sh-private
** File description:
** is_builtin
*/

#include "../../include/mysh.h"

const builtin_t builtin[] = {
    {"env", my_env},
    {"setenv", my_setenv},
    {"unsetenv", my_unsetenv},
    {"history", history},
    {"cd", my_cd},
    {"exit", my_exit},
    {"alias", my_alias},
    {"unalias", my_unalias},
    {"set", my_set},
    {"unset", my_unset},
    {NULL, NULL}
};


int is_builtin(char **args, shell_t *shell)
{
    if (args == NULL)
        return 0;
    for (int i = 0; builtin[i].name != NULL; i++){
        if (my_strcmp(args[0], builtin[i].name) == 0)
            return builtin[i].f(args, shell);
    }
    return 0;
}
