/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 03:36:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/13 19:03:44 by hsetyamu         ###   ########.fr       */
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

typedef struct s_token
{
	t_tkntype		type;
	char			*value;
	int				position;
	struct s_token	*next;
}					t_token;

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

typedef struct s_ast
{
	t_nodetype		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;				//	For command arguments
	int				args_count;			//	Number of arguments
	t_tkntype		redirection_type;	//	If it's a redirection
	char			*filename;			//	File for redirection
}					t_ast;
/*
 * Command type enumeration to identify different types of commands
 * in the command table
 */
typedef enum e_cmd_type
{
	CMD_SIMPLE,	// Simple command (e.g., ls -l)
	CMD_PIPE,	// Command part of a pipeline
	CMD_SUBSHELL// Command in subshell
}					t_cmd_type;

/*
 * Redirection structure to store input/output redirections
 */
typedef struct s_redirection
{
	t_tkntype				type;		// Type of redirection
	char					*file;		// File for redirection
	struct s_redirection	*next;	// Next redirection in list
}					t_redirection;

/*
 * Command structure to store a single command with its arguments
 * and redirections
 */
typedef struct s_command
{
	char				**args;			// Command and its arguments
	t_redirection		*redirections;	// List of redirections
	t_cmd_type			type;			// Type of command
	int					pipe_read;		// Read end of pipe (-1 if none)
	int					pipe_write;		// Write end of pipe (-1 if none)
	struct s_command	*next;			// Next command in sequence
}							t_command;

/*
 * Command table structure to store all commands to be executed
 */
typedef struct s_cmdtable
{
	t_command		*commands;		// List of commands
	int				cmd_count;		// Number of commands
	int				pipe_count;		// Number of pipes
}					t_cmdtable;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}					t_env;

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
