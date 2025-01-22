/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:18:55 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 13:19:48 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

void	handle_input_redirection(t_redirection *redirection)
{
	if (redirection->type == TKN_RDIR_IN)
		handle_input_file(redirection->file);
	else if (redirection->type == TKN_HEREDOC)
		setup_heredoc(redirection);
}

void	handle_output_file(char *filename, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_output_redirection(t_redirection *redirection)
{
	if (redirection->type == TKN_RDIR_OUT)
		handle_output_file(redirection->file, 0);
	else if (redirection->type == TKN_APPEND)
		handle_output_file(redirection->file, 1);
}

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
