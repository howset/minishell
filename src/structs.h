#ifndef STRUCTS_H
# define STRUCTS_H

# include "./minishell.h"

typedef enum e_tkntype
{
	TKN_OR,       // 0
	TKN_PIPE,     // 1
	TKN_BG,       // 2
	TKN_AND,      // 3
	TKN_RDIR_IN,  // 4
	TKN_HEREDOC,  // 5
	TKN_RDIR_OUT, // 6
	TKN_APPEND,   // 7
	TKN_SEMCOL,   // 8
	TKN_PAREN_OP, // 9
	TKN_PAREN_CL, // 10
	TKN_QUO_SIN,  // 11
	TKN_QUO_DOU,  // 12
	TKN_VAR,      // 13
	TKN_WORD,     // 14
	TKN_EOF,      // 15
	TKN_INVALID,  // 16
}					t_tkntype;

typedef struct s_token
{
	t_tkntype		type;
	char			*value;
	int position; // maybe unnecessary?
	struct s_token	*next;
	// struct s_token	*prev; //doubly linked
}					t_token;

typedef enum e_nodetype
{
	NODE_COMMAND,		// 0
	NODE_PIPE,			// 1
	NODE_AND,			// 2
	NODE_OR,			// 3
	NODE_REDIRECTION,	// 4
	NODE_SEQUENCE,		// 5
	NODE_SUBSHELL,		// 6
	NODE_INVALID		// 7
}					t_nodetype;

typedef struct s_ast
{
	t_nodetype		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char **args;                // For command arguments
	int args_count;             // Number of arguments
	t_tkntype redirection_type; // If it's a redirection
	char *filename;             // File for redirection
}					t_ast;

#endif
