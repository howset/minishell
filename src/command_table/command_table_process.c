/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:20:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 23:23:03 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

t_command	*process_command_node(t_ast *node)
{
	t_command	*cmd;
	char		**default_args;

	if (!node)
		return (NULL);
	if (node->type == NODE_REDIRECTION)
	{
		cmd = process_command_node(node->left);
		if (!cmd)
		{
			default_args = malloc(sizeof(char *) * 2);
			if (!default_args)
				return (NULL);
			default_args[0] = ft_strdup("");
			default_args[1] = NULL;
			cmd = create_command(default_args, CMD_SIMPLE);
			free(default_args[0]);
			free(default_args);
		}
		process_redirection_node(node, cmd);
		return (cmd);
	}
	if (!node->args || !node->args[0])
	{
		default_args = malloc(sizeof(char *) * 2);
		if (!default_args)
			return (NULL);
		default_args[0] = ft_strdup("");
		default_args[1] = NULL;
		cmd = create_command(default_args, CMD_SIMPLE);
		free(default_args[0]);
		free(default_args);
		return (cmd);
	}
	return (create_command(node->args, CMD_SIMPLE));
}

void	process_redirection_node(t_ast *node, t_command *cmd)
{
	t_redirection	*redir;

	if (node->left && node->left->type == NODE_REDIRECTION)
		process_redirection_node(node->left, cmd);
	redir = create_redirection(node->redirection_type, node->filename);
	if (redir)
		add_redirection(cmd, redir);
}

t_command	*process_subshell_node(t_ast *node)
{
	t_command	*cmd;

	cmd = process_command_node(node->left);
	if (cmd)
		cmd->type = CMD_SUBSHELL;
	return (cmd);
}

t_ast	*find_command_node(t_ast *node)
{
	while (node && node->type == NODE_REDIRECTION)
		node = node->left;
	return (node);
}

void	ast_to_cmdtable_recursive(t_ast *ast, t_cmdtable *table)
{
	t_command	*cmd;
	t_ast		*cmd_node;

	if (!ast || !table)
		return ;
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
		if (cmd_node)
		{
			cmd = process_command_node(cmd_node);
			if (cmd)
			{
				process_redirection_node(ast, cmd);
				add_command(table, cmd);
			}
		}
	}
	else if (ast->type == NODE_SEQUENCE)
	{
		ast_to_cmdtable_recursive(ast->left, table);
		ast_to_cmdtable_recursive(ast->right, table);
	}
	else if (ast->type == NODE_SUBSHELL)
	{
		cmd = process_subshell_node(ast);
		if (cmd)
			add_command(table, cmd);
	}
}
