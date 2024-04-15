##
## EPITECH PROJECT, 2023
## undefined
## File description:
## Makefile to compile files with the lib.
## Makefile
##

CC	=	gcc

SRC	=	src/caller.c	\
		src/command_separators.c	\
		src/error_handling_input.c	\
		src/functions.c	\
		src/interpreter.c	\
		src/main.c	\
		src/my_cd.c	\
		src/my_env.c	\
		src/my_scanf.c	\
		src/my_setenv.c	\
		src/my_unsetenv.c \
		src/right_redirections.c	\
		src/shell.c

OBJ	=	$(SRC:src/%.c=bin/%.o)

CFLAGS	=	-g3 -W -Wall

LIB_NAME	=	libmy.a

EXEC	=	42sh

all:	compile_lib $(EXEC)

compile_lib:
	make -C lib/my

$(EXEC):	$(LIB_NAME) $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) -L. -lmy $(CFLAGS)

bin/%.o:	src/%.c
	@mkdir -p bin
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)
	@rm -rf bin
	make clean -C lib/my

fclean:	clean
	rm -f $(EXEC)
	make fclean -C lib/my

re:	fclean all

.PHONY:	all compile_lib clean fclean re
