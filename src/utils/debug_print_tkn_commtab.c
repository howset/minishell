/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_tkn_commtab.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:36:42 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/16 16:01:56 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

// direct copy
void	print_tkn(t_token *tokens)
{
	t_token	*current;

	printf("\n");
	printf("Tokens:\n");
	current = tokens;
	while (current)
	{
		printf("Type: %d, Value: '%s', Position: %d\n", current->type,
			current->value, current->position);
		current = current->next;
	}
}

void	print_commargs(char **args)
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

void	print_commredirs(t_redirection *redir)
{
	while (redir)
	{
		printf("Redirection: type=%d, file=%s\n", redir->type, redir->file);
		redir = redir->next;
	}
}

void	print_commdetails(t_command *cmd)
{
	while (cmd)
	{
		printf("\nCommand:\n");
		printf("Type: %d\n", cmd->type);
		print_commargs(cmd->args);
		if (cmd->pipe_read != -1)
			printf("Pipe read fd: %d\n", cmd->pipe_read);
		if (cmd->pipe_write != -1)
			printf("Pipe write fd: %d\n", cmd->pipe_write);
		print_commredirs(cmd->redirections);
		cmd = cmd->next;
	}
}

void	print_command_table(t_cmdtable *table)
{
	if (!table)
		return ;
	printf("\nCommand Table:\n");
	printf("Total commands: %d\n", table->cmd_count);
	printf("Total pipes: %d\n", table->pipe_count);
	print_commdetails(table->commands);
	printf("\n");
}
