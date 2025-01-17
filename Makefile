##------------------------------------------------------------------##
# Variables.

## Name
NAME-MS				= minishell
NAME-LIBFT			= ./src/lib/libft.a

## Compiler, flags, & other commands
CC 					= cc
CFLAGS 				= -g -O0 -Wall -Werror -Wextra
AR					= ar rcs
RM					= rm -f
LIBS				= -lreadline

ifeq ($(shell uname), Darwin)
CFLAGS += -I/opt/homebrew/opt/readline/include
LIBS += -L/opt/homebrew/opt/readline/lib
endif


UTILS 				= 	./src/utils/malloc_perex.c\
						./src/utils/ft_fprintf.c\
						./src/utils/debug_print_tkn_commtab.c\
						./src/utils/debug_print_ast.c\
						./src/utils/prompt.c\
						./src/utils/cleanups.c

## Sources & header
SRC-MS				= 	./src/minishell.c

SRC-SIGNALS			= 	./src/signals/signals.c

SRC-LEXER			= 	./src/lexer/grouping.c \
						./src/lexer/lexer.c \
						./src/lexer/operator.c \
						./src/lexer/quote.c \
						./src/lexer/redirection.c \
						./src/lexer/token.c \
						./src/lexer/word.c

SRC-PARSER			= 	./src/parser/parser.c \
						./src/parser/parse_expression.c\
						./src/parser/parse_pipe.c\
						./src/parser/parse_term.c\
						./src/parser/parse_factor.c\
						./src/parser/parse_command.c\
						./src/parser/ast.c \
						./src/parser/utils/parser_utils.c \
						./src/parser/utils/string_processing.c \
						./src/parser/utils/env_variable_handling.c

SRC-EXEC			= 	./src/exec/exec.c \
						./src/exec/exec_builtin.c \
						./src/exec/exec_child.c \
						./src/exec/exec_pathfinding.c \
						./src/exec/exec_redirections.c \
						./src/exec/exec_redirs_in.c \
						./src/exec/exec_pipes.c \
						./src/exec/exec_pathfinding_build.c

SRC-BUILTINS		= 	./src/builtins/echo.c \
						./src/builtins/env.c \
						./src/builtins/exit.c \
						./src/builtins/export.c \
						./src/builtins/unset.c \
						./src/builtins/cd.c \
						./src/builtins/pwd.c

SRC-CMDTABLE		= 	./src/command_table/command_table_utils.c \
						./src/command_table/command_table_process.c \
						./src/command_table/command_table_pipe.c \
						./src/command_table/command_table_init.c \
						./src/command_table/command_table_free.c \
						./src/command_table/command_table_process_utils.c

SRC-ENVS 			= 	./src/envs/envlist.c \
						./src/envs/envvar.c \
						./src/envs/free_env.c

HEADER				= ./src/
ALL_SRC				= $(SRC-MS) $(SRC-LEXER) $(SRC-PARSER) $(SRC-EXEC) $(SRC-BUILTINS) $(SRC-CMDTABLE) $(SRC-ENVS) $(UTILS) $(SRC-SIGNALS)
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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=l_valgrind-out.txt ./$(NAME-MS)

test_fds:				$(NAME-LIBFT) $(NAME-MS)
	valgrind -q --tool=none --track-fds=all ./$(NAME-MS)

test_fdslog:				$(NAME-LIBFT) $(NAME-MS)
	valgrind -q --tool=none --track-fds=all --log-file=fd_valgrind-out.txt ./$(NAME-MS)

##------------------------------------------------------------------##
# Pattern rule
%.o: %.c
		@$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

##------------------------------------------------------------------##
# Targets

$(NAME-LIBFT):
		@make -C ./src/lib
		@echo "$(GREEN)Libft ready!$(COLOFF)"

$(NAME-MS): $(OBJS) $(NAME-LIBFT)
		@$(CC) $(CFLAGS) $(OBJS) $(NAME-LIBFT) -o $(NAME-MS) $(LIBS)
		@echo "$(GREEN)Minishell ready!$(COLOFF)"

##------------------------------------------------------------------##
#.PHONY

.PHONY: clean fclean all re
