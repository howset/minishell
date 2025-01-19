/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:18:10 by hsetya            #+#    #+#             */
/*   Updated: 2025/01/19 14:52:32 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Handles input file redirection
 *
 * This function opens a file specified in the redirection structure for reading
 * and redirects the standard input (stdin) to read from this file. If any error
 * occurs during file opening or redirection, the program exits with failure.
 *
 * @param redirection Pointer to redirection structure containing
 * 						file information
 *
 * @note The function will exit the program if:
 *       - The file cannot be opened
 *       - The file descriptor duplication fails
 */
void	handle_filein(t_redirection *redirection)
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

/**
 * @brief Handles heredoc input redirection
 *
 * Creates a pipe and forks a process to handle heredoc input. The child process
 * will write the heredoc content to the pipe, while the parent process waits
 * for completion and handles the pipe file descriptors.
 *
 * @param redirection Pointer to the redirection structure containing heredoc
 * 						details
 *
 * @note The function will exit with failure if pipe creation or fork fails
 * @note Child process is handled by exec_childheredoc
 * @note Parent process is handled by exec_parentheredoc
 */
void	handle_heredocin(t_redirection *redirection)
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
		exec_childheredoc(redirection, pipefd);
	else
		exec_parentheredoc(pipefd, pid);
}

/**
 * @brief Executes the child process for heredoc redirection
 *
 * This function handles the child process part of a heredoc redirection
 * operation. It repeatedly reads input lines until the delimiter
 * (redirection->file) is found.
 * Each line is written to the pipe before the delimiter is encountered.
 *
 * @param redirection Pointer to redirection structure containing heredoc
 * 						delimiter
 * @param pipefd Array containing file descriptors for the pipe
 *
 * Signal handling:
 * - SIGINT (Ctrl+C): Reset to default behavior
 * - SIGQUIT (Ctrl+\): Ignored
 *
 * Process:
 * 1. Sets up signal handling
 * 2. Closes read end of pipe
 * 3. Reads lines until delimiter is found
 * 4. Writes each line to pipe
 * 5. Exits successfully when complete
 *
 * @note Function never returns, always exits process
 */
void	exec_childheredoc(t_redirection *redirection, int pipefd[2])
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[0]);
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redirection->file) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

/**
 * Handles parent process operations for heredoc redirection
 * Redirects input from pipe to stdin and waits for child process
 *
 * @param pipefd Array containing read/write pipe file descriptors
 * @param pid Process ID of child process to wait for
 *
 * @note Closes write end of pipe and duplicates read end to stdin
 * @note Exits with child process exit status
 *
 * @exit Exits with error on dup2 failure or child process status
 */
void	exec_parentheredoc(int pipefd[2], pid_t pid)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	exit(wait_chprocess(pid));
}
