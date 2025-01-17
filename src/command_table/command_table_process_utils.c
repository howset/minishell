/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_process_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:48:31 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/17 13:50:33 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

static void	process_ast_node(t_ast *ast, t_cmdtable *table)
{
	t_command	*cmd;
	t_ast		*cmd_node;

	if (ast->type == NODE_COMMAND)
	{
		cmd = process_command_node(ast);
		if (cmd)
			add_command(table, cmd);
	}
	else if (ast->type == NODE_PIPE)
		process_pipe_node(ast, table);
	else if (ast->type == NODE_REDIRECTION)
	{
		cmd_node = find_command_node(ast);
		cmd = process_command_node(cmd_node);
		if (cmd_node && cmd)
		{
			process_redirection_node(ast, cmd);
			add_command(table, cmd);
		}
	}
}

void	ast_to_cmdtable_recursive(t_ast *ast, t_cmdtable *table)
{
	t_command	*cmd;

	if (!ast || !table)
		return ;
	if (ast->type == NODE_SEQUENCE)
	{
		ast_to_cmdtable_recursive(ast->left, table);
		ast_to_cmdtable_recursive(ast->right, table);
		return ;
	}
	if (ast->type == NODE_SUBSHELL)
	{
		cmd = process_subshell_node(ast);
		if (cmd)
			add_command(table, cmd);
		return ;
	}
	process_ast_node(ast, table);
}
