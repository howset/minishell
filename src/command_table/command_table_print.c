/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:47:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 21:49:06 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./command_table.h"

void	print_command_args(char **args)
{
	int	i;

	i = 0;
	printf("Arguments: ");
	while (args && args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
	printf("\n");
}

void	print_command_pipes(t_command *cmd)
{
	if (cmd->pipe_read != -1)
	{
		printf("Pipe read fd: %d\n", cmd->pipe_read);
	}
	if (cmd->pipe_write != -1)
	{
		printf("Pipe write fd: %d\n", cmd->pipe_write);
	}
}

void	print_redirections(t_redirection *redir)
{
	while (redir)
	{
		printf("Redirection: type=%d, file=%s\n", redir->type, redir->file);
		redir = redir->next;
	}
}

void	print_command_info(t_command *cmd)
{
	printf("\nCommand:\n");
	printf("Type: %d\n", cmd->type);
	print_command_args(cmd->args);
	print_command_pipes(cmd);
	print_redirections(cmd->redirections);
}

void	print_command_table(t_cmdtable *table)
{
	t_command	*cmd;

	if (!table)
	{
		return ;
	}
	printf("\nCommand Table:\n");
	printf("Total commands: %d\n", table->cmd_count);
	printf("Total pipes: %d\n", table->pipe_count);
	cmd = table->commands;
	while (cmd)
	{
		print_command_info(cmd);
		cmd = cmd->next;
	}
	printf("\n");
}
