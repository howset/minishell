/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:54:39 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/17 14:15:21 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H

# include "../minishell.h"
# include "../structs.h"

// command_table_init.c
t_cmdtable		*create_command_table(void);
t_command		*create_command(char **args, t_cmd_type type);
t_redirection	*create_redirection(t_tkntype type, char *file);
void			add_command(t_cmdtable *table, t_command *cmd);
void			add_redirection(t_command *cmd, t_redirection *redir);

// command_table_process.c
t_command		*process_command_node(t_ast *node);
void			process_redirection_node(t_ast *node, t_command *cmd);
t_command		*process_subshell_node(t_ast *node);
t_ast			*find_command_node(t_ast *node);
void			ast_to_cmdtable_recursive(t_ast *ast, t_cmdtable *table);

// command_table_pipe.c
void			process_pipe_node(t_ast *node, t_cmdtable *table);
t_cmdtable		*ast_to_command_table(t_ast *ast);

// command_table_utils.c
char			**duplicate_args(char **args, int count);
void			free_redirection(t_redirection *redir);
void			free_command(t_command *cmd);

// command_table_free.c
void			free_command_table(t_cmdtable *table);

//command_table_process_utils.c
void			process_ast_node(t_ast *ast, t_cmdtable *table);
void			ast_to_cmdtable_recursive(t_ast *ast, t_cmdtable *table);

#endif
