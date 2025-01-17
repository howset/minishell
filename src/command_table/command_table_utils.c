/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:20:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 23:23:03 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

static char	**allocate_args_array(int count)
{
	char	**new_args;

	if (count == 0)
	{
		new_args = malloc(sizeof(char *));
		if (!new_args)
			return (NULL);
		new_args[0] = NULL;
		return (new_args);
	}
	new_args = malloc(sizeof(char *) * (count + 1));
	if (!new_args)
		return (NULL);
	return (new_args);
}

static void	free_partial_args(char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	**duplicate_args(char **args, int count)
{
	char	**new_args;
	int		i;

	if (!args)
		return (allocate_args_array(0));
	new_args = allocate_args_array(count);
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			free_partial_args(new_args, i);
			return (NULL);
		}
		i++;
	}
	new_args[count] = NULL;
	return (new_args);
}

void	free_redirection(t_redirection *redir)
{
	t_redirection	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->file);
		free(redir);
		redir = next;
	}
}

void	free_command(t_command *cmd)
{
	t_command	*next;
	int			i;

	while (cmd)
	{
		next = cmd->next;
		free_redirection(cmd->redirections);
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		if (cmd->args)
			free(cmd->args);
		free(cmd);
		cmd = next;
	}
}
