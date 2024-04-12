/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** header of the functions from the library libmy
** functions
*/

#ifndef MY_H_
    #define MY_H_
    #include <stdbool.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdarg.h>

typedef struct separate_words_s {
    char **tab;
    char const *str;
    char const *sep;
} separate_words_t;

void my_putchar(char c);
int my_isneg(int nb);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
int my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
char *concat_params(int argc, char **argv);
int my_show_word_array(char *const *tab);
char *my_strdup(char const *src);
char **my_str_to_word_array(char const *str);
int my_strlen_array(char **array);
int my_intlen(int n);
int convert_str_in_int(char *str);
char *concat_2_str(char *str1, char *str2);
char *my_strndup(char const *src, int n);
char *convert_int_to_str(int nbr);
int my_abs(int nbr);
char **separate_words_on_spaces(char const *str);
int mini_printf(const char *format, ...);
char **separate_words(char const *str, char const *sep);
void free_word_array(char **word_array);
char *concat_str(int nb_elt, ...);
char *parse_str(char const *str, int ind_start, int ind_end);
char **my_tabdup(char **tab);
char **separate_words_on_str(char const *str, char const *sep);
void my_fdputchar(int fd, char c);
int my_fdputstr(int fd, char const *str);
int my_fdput_nbr(int fd, int nb);
int mini_fdprintf(int fd, const char *format, ...);
void print_word_array(char **word_array);
void multiple_free(int nb_free, ...);
void multiple_free_word_array(int nb_free, ...);
char *clean_str(char *str, int destroy);
char *clean_str_on_char(char *str, char *unwanted);

#endif
