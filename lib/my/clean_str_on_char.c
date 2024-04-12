/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** removes unwanted characters
** clean_str
*/

#include "my.h"

int is_unwanted(char c, char *unwanted)
{
    for (int i = 0; unwanted[i] != '\0'; i++) {
        if (c == unwanted[i])
            return 1;
    }
    return 0;
}

char *clean_str_on_char(char *str, char *unwanted)
{
    int length = 0;
    int pos = 0;
    char *result;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_unwanted(str[i], unwanted))
            length++;
    }
    result = malloc(sizeof(char) * length + 1);
    for (int i2 = 0; str[i2] != '\0'; i2++) {
        if (!is_unwanted(str[i2], unwanted)) {
            result[pos] = str[i2];
            pos++;
        }
    }
    result[length] = '\0';
    return result;
}
