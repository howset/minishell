/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:54:39 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 21:49:06 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H

# include "../minishell.h"
# include "../structs.h"

// Function prototypes
t_cmdtable		*create_command_table(void);
void			free_command_table(t_cmdtable *table);
t_cmdtable		*ast_to_command_table(t_ast *ast);
t_command		*create_command(char **args, t_cmd_type type);
t_redirection	*create_redirection(t_tkntype type, char *file);
void			add_command(t_cmdtable *table, t_command *cmd);
void			add_redirection(t_command *cmd, t_redirection *redir);
char			**duplicate_args(char **args, int count);
t_command		*process_command_node(t_ast *node);
void			process_pipe_node(t_ast *node, t_cmdtable *table);
void			process_redirection_node(t_ast *node, t_command *cmd);
t_command		*process_subshell_node(t_ast *node);
t_ast			*find_command_node(t_ast *node);
void			ast_to_cmdtable_recursive(t_ast *ast, t_cmdtable *table);
t_cmdtable		*ast_to_command_table(t_ast *ast);
void			free_redirection(t_redirection *redir);
void			free_command(t_command *cmd);
void			free_command_table(t_cmdtable *table);
// Command table printing functions
void	print_command_table(t_cmdtable *table);
void	print_command_info(t_command *cmd);
void	print_command_args(char **args);
void	print_command_pipes(t_command *cmd);
void	print_redirections(t_redirection *redir);

#endif
