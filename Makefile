##------------------------------------------------------------------##
# Variables.

## Name
NAME-MS				= minishell
NAME-LIBFT			= ./src/lib/libft.a

## Compiler, flags, & other commands
CC 					= cc
CFLAGS 				= -g -O0 -Wall -Werror -Wextra -I
AR					= ar rcs
RM					= rm -f
LIBS				= -lreadline

UTILS 				= 	./src/utils/malloc_perex.c\
						./src/utils/ft_fprintf.c

## Sources & header
SRC-MS				= 	./src/minishell.c


SRC-LEXER			= 	./src/lexer/grouping.c \
						./src/lexer/lexer.c \
						./src/lexer/operator.c \
						./src/lexer/quote.c \
						./src/lexer/redirection.c \
						./src/lexer/token.c \
						./src/lexer/word.c

SRC-PARSER			= 	./src/parser/parser.c \
						./src/parser/parser_utils.c \
						./src/parser/ast.c \
						./src/parser/comm_table.c \
						./src/parser/comm_table_utils.c

SRC-EXEC			= 	./src/exec/exec.c \
						./src/exec/exec_child.c \
						./src/exec/exec_pathfinding.c

SRC-BUILTINS		= 	./src/builtins/echo.c \
						./src/builtins/env.c \
						./src/builtins/exit.c \
						./src/builtins/export.c \
						./src/builtins/export_sort.c \
						./src/builtins/unset.c


HEADER				= ./src/
ALL_SRC				= $(SRC-MS) $(SRC-LEXER) $(SRC-PARSER) $(SRC-EXEC) $(SRC-BUILTINS) $(UTILS)
OBJS				= $(ALL_SRC:.c=.o)

## Text colors
RED					=	\033[1;31m
GREEN				=	\033[1;32m
COLOFF				=	\033[0m

##------------------------------------------------------------------##
# Build rules

all:				$(NAME-LIBFT) $(NAME-MS)

#bonus:				$(NAME-LIBFT) $(NAME-BONUS)

clean:
					@$(RM) $(OBJS) $(NAME-MS)
					@echo "$(RED)Minishell's gone, baby, gone!$(COLOFF)"

fclean:				clean
					@make fclean -C ./src/lib
					@echo "$(RED)Libft's gone, baby, gone!$(COLOFF)"

re:					fclean all

#re-bonus:			fclean bonus


test:
		@make -C tests -f Makefile run
		@echo "$(GREEN)Tests executed!$(COLOFF)"

test_val:				$(NAME-LIBFT) $(NAME-MS)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME-MS)

test_vallog:			$(NAME-LIBFT) $(NAME-MS)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME-MS)

##------------------------------------------------------------------##
# Pattern rule
%.o: %.c
		@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

##------------------------------------------------------------------##
# Targets

$(NAME-LIBFT):
		@make -C ./src/lib
		@echo "$(GREEN)Libft ready!$(COLOFF)"

$(NAME-MS): $(OBJS) $(NAME-LIBFT)
		@$(CC) $(CFLAGS) $(HEADER) $(OBJS) $(NAME-LIBFT) -o $(NAME-MS) $(LIBS)
		@echo "$(GREEN)Minishell ready!$(COLOFF)"

##------------------------------------------------------------------##
#.PHONY

.PHONY: clean fclean all re
