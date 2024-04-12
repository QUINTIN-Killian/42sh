##
## EPITECH PROJECT, 2023
## undefined
## File description:
## Makefile for mylib
## Makefile
##

CC	=	gcc

SRC	=	clean_str.c \
		clean_str_on_char.c \
		concat_2_str.c  \
		concat_params.c \
		concat_str.c    \
		convert_int_to_str.c    \
		convert_str_in_int.c    \
		free_word_array.c   \
		mini_fdprintf.c \
		mini_printf.c   \
		multiple_free.c \
		multiple_free_word_array.c  \
		my_abs.c    \
		my_compute_power_rec.c  \
		my_compute_square_root.c    \
		my_fdputchar.c  \
		my_fdput_nbr.c  \
		my_fdputstr.c   \
		my_find_prime_sup.c \
		my_getnbr.c \
		my_intlen.c \
		my_isneg.c  \
		my_is_prime.c   \
		my_putchar.c    \
		my_put_nbr.c    \
		my_putstr.c \
		my_revstr.c \
		my_show_word_array.c    \
		my_sort_int_array.c \
		my_strcapitalize.c  \
		my_strcat.c \
		my_strcmp.c \
		my_strcpy.c \
		my_strdup.c \
		my_str_isalpha.c    \
		my_str_islower.c    \
		my_str_isnum.c  \
		my_str_isprintable.c    \
		my_str_isupper.c    \
		my_strlen_array.c   \
		my_strlen.c \
		my_strlowcase.c \
		my_strncat.c    \
		my_strncmp.c    \
		my_strncpy.c    \
		my_strndup.c    \
		my_strstr.c \
		my_str_to_word_array.c  \
		my_strupcase.c  \
		my_swap.c   \
		my_tabdup.c \
		parse_str.c \
		print_word_array.c  \
		sep_str.c	\
		separate_words.c    \
		separate_words_on_spaces.c  \
		separate_words_on_str.c


OBJ	=	$(SRC:%.c=bin/%.o)

CFLAGS	=	-g3 -W -Wall

H_NAME	=	my.h

LIB_NAME	=	libmy.a

all:	$(LIB_NAME)

$(LIB_NAME):	$(OBJ)
	ar rc $(LIB_NAME) $(OBJ)
	cp $(LIB_NAME) ../..
	cp $(H_NAME) ../../include

bin/%.o:	%.c
	@mkdir -p bin
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)
	@rm -rf bin

fclean:	clean
	rm -f $(LIB_NAME) ../../$(LIB_NAME)

re:	fclean all

.PHONY:	all clean fclean re
