/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:42:35 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 21:49:06 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "string.h"

void	handle_simple_input(t_redirection *redirection)
{
	int	fd;

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

void	process_heredoc_child(int write_fd, char *delimiter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			break ;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(EXIT_SUCCESS);
}

void	process_heredoc_parent(int read_fd, pid_t child_pid)
{
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(read_fd);
	waitpid(child_pid, NULL, 0);
}

void	handle_heredoc_input(t_redirection *redirection)
{
	int		pipefd[2];
	pid_t	pid;

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
	if (pid == 0)
	{
		close(pipefd[0]);
		process_heredoc_child(pipefd[1], redirection->file);
	}
	else
	{
		close(pipefd[1]);
		process_heredoc_parent(pipefd[0], pid);
	}
}

void	handle_input_redirection(t_redirection *redirection)
{
	if (redirection->type == TKN_RDIR_IN)
	{
		handle_simple_input(redirection);
	}
	else if (redirection->type == TKN_HEREDOC)
	{
		handle_heredoc_input(redirection);
	}
}

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

void	exec_redirections(t_redirection *redirections)
{
	t_redirection	*current;

	current = redirections;
	while (current)
	{
		if (current->type == TKN_RDIR_IN || current->type == TKN_HEREDOC)
		{
			handle_input_redirection(current);
		}
		else if (current->type == TKN_RDIR_OUT || current->type == TKN_APPEND)
		{
			handle_output_redirection(current);
		}
		current = current->next;
	}
}
