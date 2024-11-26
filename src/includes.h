#ifndef INCLUDES_H
# define INCLUDES_H

# include "./lib/src/ft_printf/ft_printf.h"
# include "./lib/src/get_next_line/get_next_line.h"
# include "./lib/src/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_tkntype
{
	TKN_OR, //0
	TKN_PIPE, //1
	TKN_BG, //2
	TKN_AND, //3
	TKN_RDIR_IN, //4
	TKN_HEREDOC, //5
	TKN_RDIR_OUT, //6
	TKN_APPEND, //7
	TKN_SEMCOL, //8
	TKN_PAREN_OP, //9
	TKN_PAREN_CL, //10
	TKN_QUO_SIN, //11
	TKN_QUO_DOU, //12
	TKN_VAR, //13
	TKN_WORD, //14
	TKN_EOF, //15
	TKN_INVALID, //16
}	t_tkntype;

typedef struct s_token{
	t_tkntype		type;
	char			*value;
	int				position;
	struct s_token	*next;
	//struct s_token	*prev; //doubly linked
}	t_token;

// Token and parser data structures
typedef enum {
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_BACKGROUND
} NodeType;

typedef struct ASTNode {
	NodeType type;
	char *value;				// Command name or operator
	struct ASTNode *left;		// Left child (e.g., for pipelines)
	struct ASTNode *right;		// Right child (e.g., for arguments or pipelines)
} ASTNode;

typedef struct {
	t_token *tokens;
	t_token *current;
} Parser;

// utils
void	*malloc_perex(size_t bytes, char *msg);

#endif