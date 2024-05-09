/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** utility.c
*/

#include "../include/my.h"

#include <stdbool.h>

char *concat(char *str1, char *str2)
{
    char *res = malloc(my_strlen(str1) + my_strlen(str2) + 1);

    if (str1 == NULL && str2 == NULL)
        return NULL;
    if (str1 != NULL)
        res = strcpy(res, str1);
    else {
        res = strcpy(res, str2);
        return res;
    }
    if (str2 != NULL)
        res = strcat(res, str2);
    return res;
}

bool char_in_string(char c, char *string)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] == c)
            return true;
    return false;
}

char *string_to_delims(char *input, char *delimiters)
{
    char *token;
    int size = 0;

    for (; !char_in_string(input[size], delimiters) &&
        input[size] != '\0'; size++);
    if (size == 0)
        return NULL;
    token = malloc(size + 1);
    for (int i = 0; i < size; i++)
        token[i] = input[i];
    token[size] = '\0';
    return token;
}
