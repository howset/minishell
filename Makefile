##------------------------------------------------------------------##
# Variables.

## Name
NAME-MS				= minishell
NAME-LIBFT			= ./src/lib/libft.a

## Compiler, flags, & other commands
CC 					= cc
CFLAGS 				= -g -Wall -Werror -Wextra -I
AR					= ar rcs
RM					= rm -f
LIBS				= -lreadline

## Sources & header
SRC-MS				= ./src/main.c \
						./src/lexer/lexer.c \
						./src/lexer/lexer_utils1.c \
						./src/lexer/lexer_utils2.c \
						./src/utils_wrapper.c
HEADER				= ./src/

## Text colors
RED					=	\033[1;31m
GREEN				=	\033[1;32m
COLOFF				=	\033[0m

##------------------------------------------------------------------##
# Build rules

all:				$(NAME-LIBFT) $(NAME-MS)

#bonus:				$(NAME-LIBFT) $(NAME-BONUS)

clean:
					@$(RM) $(NAME-MS)
					@echo "$(RED)Minishell's gone, baby, gone!$(COLOFF)"

fclean:				clean
					@make fclean -C ./src/lib
					@echo "$(RED)Libft's gone, baby, gone!$(COLOFF)"

re:					fclean all

re-bonus:			fclean bonus

test:				$(NAME-LIBFT) $(NAME-MS)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME-MS)

test_log:			$(NAME-LIBFT) $(NAME-MS)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME-MS)

##------------------------------------------------------------------##
# Targets
$(NAME-LIBFT):
		@make -C ./src/lib
		@echo "$(GREEN)Libft ready!$(COLOFF)"

$(NAME-MS): ./src/main.c $(NAME-LIBFT)
		@$(CC) $(CFLAGS) $(HEADER) $(SRC-MS) $(NAME-LIBFT) -o $(NAME-MS) $(LIBS)
		@echo "$(GREEN)Minishell ready!$(COLOFF)"

##------------------------------------------------------------------##
#.PHONY
.PHONY: clean fclean all re
