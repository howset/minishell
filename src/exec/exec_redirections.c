/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:42:35 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/19 00:18:20 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * Handle input redirection ("<" and "<<").
 * @param redirection The redirection structure.
 */
void	handle_input_redirection(t_redirection *redirection)
{
	if (redirection->type == TKN_RDIR_IN)
		handle_filein(redirection);
	else if (redirection->type == TKN_HEREDOC)
		handle_heredocin(redirection);
}

/**
 * Handle output redirection (">" and ">>").
 * @param redirection The redirection structure.
 */
void	handle_output_redirection(t_redirection *redirection)
{
	int	fd;

	if (redirection->type == TKN_RDIR_OUT)
	{
		fd = open(redirection->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redirection->type == TKN_APPEND)
	{
		fd = open(redirection->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

/**
 * Apply all redirections for a command.
 * @param redirections The list of redirections.
 */
void	exec_redirections(t_redirection *redirections)
{
	t_redirection	*current;

	current = redirections;
	while (current)
	{
		if (current->type == TKN_RDIR_IN || current->type == TKN_HEREDOC)
			handle_input_redirection(current);
		else if (current->type == TKN_RDIR_OUT || current->type == TKN_APPEND)
			handle_output_redirection(current);
		current = current->next;
	}
}
