##------------------------------------------------------------------##
# Variables.

## Compiler, flags, & other commands
CC      = cc
CFLAGS  = -g -Wall -Wextra -I../src
RM      = rm -f
LIBS    = -lreadline

## Sources & headers
UTILS   = ../src/utils/malloc_perex.c
SRC_MS  = ../src/lexer/grouping.c \
		  ../src/lexer/lexer.c \
		  ../src/lexer/operator.c \
		  ../src/lexer/quote.c \
		  ../src/lexer/redirection.c \
		  ../src/lexer/token.c \
		  ../src/lexer/word.c

HEADER  = ../src/
LIBFT   = ../src/lib/libft.a

LEXER_TESTS = ./lexer/lexer_grouping_test.c \
			  ./lexer/lexer_operator_test.c \
			  ./lexer/lexer_quote_test.c \
			  ./lexer/lexer_redirection_test.c \
			  ./lexer/lexer_word_test.c 
## Test sources
TEST_SRCS   = main_test.c $(LEXER_TESTS)
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

$(TEST_EXEC): $(TEST_SRCS) $(SRC_MS) $(UTILS) $(LIBFT)
	$(CC) $(CFLAGS) $(TEST_SRCS) $(SRC_MS) $(UTILS) $(LIBFT) -o $(TEST_EXEC) $(CHECK_LIBS) $(LIBS)

run:    $(TEST_EXEC)
	./$(TEST_EXEC)

# .PHONY
.PHONY: clean all run