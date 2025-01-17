/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:20:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/17 13:50:31 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

t_command	*create_empty_command(void)
{
	t_command	*cmd;
	char		**default_args;

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

t_command	*process_command_node(t_ast *node)
{
	t_command	*cmd;

	if (!node)
		return (NULL);
	if (node->type == NODE_REDIRECTION)
	{
		cmd = process_command_node(node->left);
		if (!cmd)
			cmd = create_empty_command();
		if (cmd)
			process_redirection_node(node, cmd);
		return (cmd);
	}
	if (!node->args || !node->args[0])
		return (create_empty_command());
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
