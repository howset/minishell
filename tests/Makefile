##------------------------------------------------------------------##
# Variables.

## Compiler, flags, & other commands
CC      = cc
CFLAGS  = -g -Wall -Wextra -I../src
RM      = rm -f
LIBS    = -lreadline

## Sources & headers
UTILS   			= ../src/utils/malloc_perex.c \
					  ../src/utils/ft_fprintf.c

SRC-LEXER			= 	../src/lexer/grouping.c \
						../src/lexer/lexer.c \
						../src/lexer/operator.c \
						../src/lexer/quote.c \
						../src/lexer/redirection.c \
						../src/lexer/token.c \
						../src/lexer/word.c

SRC-PARSER			= 	../src/parser/parser.c \
						../src/parser/parser_utils.c \
						../src/parser/ast.c \
						../src/parser/comm_table.c \
						../src/parser/comm_table_utils.c

SRC-EXEC			= 	../src/exec/exec.c \
						../src/exec/exec_child.c \
						../src/exec/exec_pathfinding.c

SRC-BUILTINS		= 	../src/builtins/echo.c \
						../src/builtins/env.c \
						../src/builtins/exit.c \
						../src/builtins/export.c \
						../src/builtins/export_sort.c \
						../src/builtins/unset.c \
						../src/builtins/pwd.c

ALL_SRC				= $(SRC-LEXER) $(SRC-PARSER) $(SRC-EXEC) $(SRC-BUILTINS) $(UTILS)


HEADER  = ../src/
LIBFT   = ../src/lib/libft.a

LEXER_TESTS = ./lexer/lexer_grouping_test.c \
			  ./lexer/lexer_operator_test.c \
			  ./lexer/lexer_quote_test.c \
			  ./lexer/lexer_redirection_test.c \
			  ./lexer/lexer_word_test.c

# Add parser tests to PARSER_TESTS variable
PARSER_TESTS = ./parser/parser_simple_command_test.c \
               ./parser/parser_pipe_test.c \
               ./parser/parser_redirection_test.c \
               ./parser/parser_logical_test.c

BUILTINS_TESTS =  ./builtins/builtin_pwd_test.c \
				  ./builtins/builtin_unset_test.c \
				  ./builtins/builtin_export_test.c \
				  ./builtins/builtin_echo_test.c

HELPERS = ./helpers/env.c
TEST_HEADER = ./tests.h
## Test sources
# Update TEST_SRCS to include parser tests
TEST_SRCS   = main_test.c $(LEXER_TESTS) $(PARSER_TESTS) $(BUILTINS_TESTS) $(HELPERS)
TEST_EXEC   = test_runner

##------------------------------------------------------------------##
# Build rules

all:    $(TEST_EXEC)

clean:
	@$(RM) $(TEST_EXEC)
	@echo "Test executable removed!"

##------------------------------------------------------------------##
# Targets

CHECK_LIBS = $(shell pkg-config --cflags --libs check)

$(TEST_EXEC): $(TEST_SRCS) $(ALL_SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(TEST_SRCS) $(ALL_SRC) $(LIBFT) -o $(TEST_EXEC) $(CHECK_LIBS) $(LIBS)

run:    $(TEST_EXEC)
	./$(TEST_EXEC)

# .PHONY
.PHONY: clean all run
