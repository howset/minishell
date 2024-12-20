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

typedef struct s_simcomm
{
	char 	**args;				// Array of command + args
	char	*in_redir;			// Input redirs
	char	*out_redir;			// Output redirs
	int		is_bg;		// FLag if command runs in background
}					t_simcomm;	// Struct for *a* simple command

typedef struct s_commtab
{
	t_simcomm *commands;		// Array of simple commands
	int count;					// Count of simple commands
}					t_commtab;

typedef struct s_env
{
	char *key;
	char *val;
	struct s_env *next;
}					t_env;

typedef struct s_alldata
{
	char 		*input;
	t_token 	*tokens;
	t_ast 		*tree;
	t_commtab 	*table;
	int			exit_stat;
	t_env		*env_head;
	t_env		**env_list;
}					t_alldata;

#endif
