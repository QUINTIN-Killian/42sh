/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** writes a character in a file
** my_fdputchar
*/

#include "my.h"

void my_fdputchar(int fd, char c)
{
    write(fd, &c, 1);
}
