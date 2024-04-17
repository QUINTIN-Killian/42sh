##
## EPITECH PROJECT, 2023
## undefined
## File description:
## Makefile to compile files with the lib.
## Makefile
##

CC	=	gcc

SRC	=	src/command_separators.c	\
		src/error_handling_input.c	\
		src/functions.c	\
		src/main.c	\
		src/builtin/my_cd.c	\
		src/builtin/my_env.c	\
		src/my_scanf.c	\
		src/builtin/my_setenv.c	\
		src/var_env.c	\
		src/builtin/my_unsetenv.c \
		src/shell.c	\
		src/builtin/exit.c	\
		src/builtin/history.c	\
		src/ast/ast.c	\
		src/ast/ast_parse.c	\
		src/ast/ast_execute.c	\
		src/ast/exec_util.c	\
		src/ast/operator_executor.c	\
		src/ast/operator_executor2.c	\

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
	@mkdir -p bin/ast
	@mkdir -p bin/builtin
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
