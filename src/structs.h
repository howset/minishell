/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 03:36:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/19 13:55:18 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./minishell.h"

typedef enum e_tkntype
{
	TKN_OR,
	TKN_PIPE,
	TKN_BG,
	TKN_AND,
	TKN_RDIR_IN,
	TKN_HEREDOC,
	TKN_RDIR_OUT,
	TKN_APPEND,
	TKN_SEMCOL,
	TKN_PAREN_OP,
	TKN_PAREN_CL,
	TKN_QUO_SIN,
	TKN_QUO_DOU,
	TKN_VAR,
	TKN_WORD,
	TKN_EOF,
	TKN_INVALID,
}					t_tkntype;

typedef enum e_nodetype
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_REDIRECTION,
	NODE_SEQUENCE,
	NODE_SUBSHELL,
	NODE_INVALID,
}					t_nodetype;

/*
 * Command type enumeration to identify different types of commands
 * in the command table
 */
typedef enum e_cmd_type
{
	CMD_SIMPLE,
	CMD_PIPE,
	CMD_SUBSHELL,
}					t_cmd_type;

/**
 * @struct s_token
 * @brief Represents a token in the minishell.
 *
 * This structure is used to represent a token in the minishell. A token
 * consists of a type, a value, a position, and a pointer to the next token
 * in the list.
 *
 * @var t_token::type
 * 	The type of the token, represented by the t_tkntype enumeration.
 * @var t_token::value
 * 	The value of the token, stored as a string.
 * @var t_token::position
 * 	The position of the token in the input string.
 * @var t_token::next
 * 	A pointer to the next token in the list.
 */
typedef struct s_token
{
	t_tkntype		type;
	char			*value;
	int				position;
	struct s_token	*next;
}					t_token;

/**
 * @struct s_ast
 * @brief Represents an abstract syntax tree (AST) node.
 *
 * This structure is used to represent nodes in an abstract syntax tree,
 * which is a hierarchical tree representation of the structure of source code.
 *
 * @var t_ast::type
 * 	The type of the node, represented by the t_nodetype enum.
 * @var t_ast::left
 * 	Pointer to the left child node in the AST.
 * @var t_ast::right
 * 	Pointer to the right child node in the AST.
 * @var t_ast::args
 * 	Array of arguments associated with the node.
 * @var t_ast::args_count
 * 	The number of arguments in the args array.
 * @var t_ast::redirection_type
 * 	The type of redirection, represented by the t_tkntype enum.
 * @var t_ast::filename
 * 	The filename associated with the redirection, if any.
 */
typedef struct s_ast
{
	t_nodetype		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	int				args_count;
	t_tkntype		redirection_type;
	char			*filename;
}					t_ast;

/*
 * Redirection structure to store input/output redirections
 */
/**
 * @struct s_redirection
 * @brief Represents a redirection in a shell command.
 *
 * This structure is used to store information about a redirection
 * in a shell command, including the type of redirection, the file
 * associated with the redirection, and a pointer to the next
 * redirection in the list.
 *
 * @var s_redirection::type
 * 	The type of the redirection (e.g., input, output, append).
 * @var s_redirection::file
 * 	The file associated with the redirection.
 * @var s_redirection::next
 * 	Pointer to the next redirection in the list.
 */
typedef struct s_redirection
{
	t_tkntype				type;
	char					*file;
	struct s_redirection	*next;
}							t_redirection;

/*
 * Command structure to store a single command with its arguments
 * and redirections
 */
typedef struct s_command
{
	char				**args;
	t_redirection		*redirections;
	t_cmd_type			type;
	int					pipe_read;
	int					pipe_write;
	struct s_command	*next;
}						t_command;

/*
 * Command table structure to store all commands to be executed
 */
typedef struct s_cmdtable
{
	t_command		*commands;
	int				cmd_count;
	int				pipe_count;
}					t_cmdtable;

/**
 * @struct s_env
 * @brief A structure to represent an environment variable.
 *
 * This structure is used to store an environment variable as a key-value pair.
 * It also includes a pointer to the next environment variable in the list,
 * allowing the creation of a linked list of environment variables.
 *
 * @var s_env::key
 * 	The key of the environment variable (e.g., "PATH").
 * @var s_env::val
 * 	The value of the environment variable (e.g., "/usr/bin").
 * @var s_env::next
 * 	A pointer to the next environment variable in the linked list.
 */
typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}					t_env;

/**
 * @struct s_pipeline_data
 * @brief Structure to hold data related to a pipeline of commands.
 *
 * @var s_pipeline_data::last_cmd
 * 	Pointer to the last command in the pipeline.
 * @var s_pipeline_data::env_list
 * 	Pointer to an array of environment variables.
 * @var s_pipeline_data::envp
 * 	Pointer to an array of environment strings.
 * @var s_pipeline_data::prev_pipe
 * 	Array to hold the file descriptors for the previous pipe.
 * @var s_pipeline_data::status
 * 	Integer to hold the status of the pipeline execution.
 */
typedef struct s_pipeline_data
{
	t_command	*last_cmd;
	t_env		**env_list;
	char		**envp;
	int			prev_pipe[2];
	int			status;
}				t_pipeline_data;

/**
 * @struct s_alldata
 * @brief A structure to hold all data related to the minishell program.
 *
 * This structure contains various elements that are used throughout the
 * minishell program, including user input, tokens, abstract syntax tree,
 * command table, exit status, and environment variables.
 *
 * @var s_alldata::input
 * 	A pointer to a string that holds the user input.
 * @var s_alldata::tokens
 * 	A pointer to a list of tokens generated from the user input.
 * @var s_alldata::tree
 * 	A pointer to the abstract syntax tree (AST) generated from the tokens.
 * @var s_alldata::table
 * 	A pointer to the command table generated from the AST.
 * @var s_alldata::exit_stat
 * 	An integer representing the exit status of the last executed command.
 * @var s_alldata::env_head
 * 	A pointer to the head of the environment variables linked list.
 * @var s_alldata::env_list
 * 	A pointer to an array of pointers to environment variables.
 */
typedef struct s_alldata
{
	char			*input;
	t_token			*tokens;
	t_ast			*tree;
	t_cmdtable		*table;
	int				exit_stat;
	t_env			*env_head;
	t_env			**env_list;
}					t_alldata;

#endif
