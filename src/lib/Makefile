##------------------------------------------------------------------##
# Variables.

## Name
NAME					= libft.a

## Compiler, flags, & other commands
CC 					= cc
CFLAGS 					= -Wall -Werror -Wextra -I
AR					= ar rcs
RM					= rm -f

## Directories
DIR_LFT					= src/libft/
DIR_FPF					= src/ft_printf/
DIR_GNL					= src/get_next_line/

## Sources
SRC					= $(DIR_FPF)ft_printf.c \
					$(DIR_FPF)ft_printf_c.c \
					$(DIR_FPF)ft_printf_s.c \
					$(DIR_FPF)ft_printf_di.c \
					$(DIR_FPF)ft_printf_u.c \
					$(DIR_FPF)ft_printf_p.c \
					$(DIR_FPF)ft_printf_hex.c \
					$(DIR_GNL)get_next_line.c \
					$(DIR_GNL)get_next_line_utils.c \
					$(DIR_GNL)get_next_line_bonus.c \
					$(DIR_GNL)get_next_line_utils_bonus.c \
					$(DIR_GNL)get_next_line.c \
					$(DIR_LFT)ft_isalpha.c \
					$(DIR_LFT)ft_isdigit.c \
					$(DIR_LFT)ft_isalnum.c \
					$(DIR_LFT)ft_isascii.c \
					$(DIR_LFT)ft_isprint.c \
					$(DIR_LFT)ft_strlen.c \
					$(DIR_LFT)ft_memset.c \
					$(DIR_LFT)ft_bzero.c \
					$(DIR_LFT)ft_memcpy.c \
					$(DIR_LFT)ft_memmove.c \
					$(DIR_LFT)ft_strlcpy.c \
					$(DIR_LFT)ft_strlcat.c \
					$(DIR_LFT)ft_toupper.c \
					$(DIR_LFT)ft_tolower.c \
					$(DIR_LFT)ft_strchr.c \
					$(DIR_LFT)ft_strrchr.c \
					$(DIR_LFT)ft_strncmp.c \
					$(DIR_LFT)ft_strcmp.c \
					$(DIR_LFT)ft_memchr.c \
					$(DIR_LFT)ft_memcmp.c \
					$(DIR_LFT)ft_strnstr.c \
					$(DIR_LFT)ft_atoi.c \
					$(DIR_LFT)ft_calloc.c \
					$(DIR_LFT)ft_strdup.c \
					$(DIR_LFT)ft_substr.c \
					$(DIR_LFT)ft_strjoin.c \
					$(DIR_LFT)ft_strtrim.c \
					$(DIR_LFT)ft_split.c \
					$(DIR_LFT)ft_itoa.c \
					$(DIR_LFT)ft_strmapi.c \
					$(DIR_LFT)ft_striteri.c \
					$(DIR_LFT)ft_putchar_fd.c \
					$(DIR_LFT)ft_putstr_fd.c \
					$(DIR_LFT)ft_putendl_fd.c \
					$(DIR_LFT)ft_putnbr_fd.c \
					$(DIR_LFT)ft_lstadd_back.c \
					$(DIR_LFT)ft_lstadd_front.c \
					$(DIR_LFT)ft_lstclear.c \
					$(DIR_LFT)ft_lstdelone.c \
					$(DIR_LFT)ft_lstiter.c \
					$(DIR_LFT)ft_lstlast.c \
					$(DIR_LFT)ft_lstmap.c \
					$(DIR_LFT)ft_lstnew.c \
					$(DIR_LFT)ft_lstsize.c \
					$(DIR_LFT)ft_atol.c \
					$(DIR_LFT)ft_isspace.c \
					$(DIR_LFT)ft_realloc.c \
					$(DIR_LFT)ft_isnumber.c \

OBJ					= $(SRC:.c=.o)


##------------------------------------------------------------------##
# Build rules

all:					$(NAME)

$(NAME):				$(OBJ)
					@$(AR) $(NAME) $(OBJ)

.c.o:
					@$(CC) $(CFLAGS) -I./src -c $< -o $(<:.c=.o)

clean:
					@$(RM) $(OBJ)

fclean:					clean
					$(RM) $(NAME)

re:					fclean all

##------------------------------------------------------------------##
#.PHONY
.PHONY: clean fclean all re
