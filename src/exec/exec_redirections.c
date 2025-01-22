/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:42:35 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 22:36:25 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "string.h"

/**
 * Handle input redirection ("<" and "<<").
 * @param redirection The redirection structure.
 */
void	handle_input_redirection(t_redirection *redirection)
{
	int		fd;
	int		pipefd[2];
	pid_t	pid;
	char	*line;

	if (redirection->type == TKN_RDIR_IN) // "<"
	{
		fd = open(redirection->file, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
	else if (redirection->type == TKN_HEREDOC) // "<<"
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // Child process
		{
			signal(SIGINT, SIG_DFL); // Restore default SIGINT behavior
			signal(SIGQUIT, SIG_IGN); // Restore default SIGINT behavior
			close(pipefd[0]);        // Close read end
			line = NULL;
			while (1)
			{
				line = readline("> ");
				if (!line)
					break ;
				if (strcmp(line, redirection->file) == 0)
				{
					free(line);
					break ;
				}
				write(pipefd[1], line, strlen(line));
				write(pipefd[1], "\n", 1);
				free(line);
			}
			close(pipefd[1]);
			exit(EXIT_SUCCESS);
		}
		else // Parent process
		{
			close(pipefd[1]); // Close write end
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(pipefd[0]);
			exit(wait_chprocess(pid));
		}
	}
}

/**
 * Handle output redirection (">" and ">>").
 * @param redirection The redirection structure.
 */
void	handle_output_redirection(t_redirection *redirection)
{
	int	fd;

	if (redirection->type == TKN_RDIR_OUT) // ">"
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
	else if (redirection->type == TKN_APPEND) // ">>"
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
