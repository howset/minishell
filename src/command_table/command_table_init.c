/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:20:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 23:23:03 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

t_cmdtable	*create_command_table(void)
{
	t_cmdtable	*table;

	table = malloc(sizeof(t_cmdtable));
	if (!table)
		return (NULL);
	table->commands = NULL;
	table->cmd_count = 0;
	table->pipe_count = 0;
	return (table);
}

t_command	*create_command(char **args, t_cmd_type type)
{
	t_command	*cmd;
	int			count;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	count = 0;
	while (args && args[count])
		count++;
	cmd->args = duplicate_args(args, count);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->redirections = NULL;
	cmd->type = type;
	cmd->pipe_read = -1;
	cmd->pipe_write = -1;
	cmd->next = NULL;
	return (cmd);
}

t_redirection	*create_redirection(t_tkntype type, char *file)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

void	add_command(t_cmdtable *table, t_command *cmd)
{
	t_command	*current;

	if (!table->commands)
	{
		table->commands = cmd;
	}
	else
	{
		current = table->commands;
		while (current->next)
			current = current->next;
		current->next = cmd;
	}
	table->cmd_count++;
}

void	add_redirection(t_command *cmd, t_redirection *redir)
{
	t_redirection	*current;

	if (!cmd->redirections)
	{
		cmd->redirections = redir;
	}
	else
	{
		current = cmd->redirections;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}
