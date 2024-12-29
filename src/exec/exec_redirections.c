#include "exec.h"

/**
 * Handle input redirection ("<" and "<<").
 * @param redirection The redirection structure.
 */
 void	handle_input_redirection(t_redirection *redirection)
{
	int	fd;

	if (redirection->type == TKN_RDIR_IN) // "<"
	{
		fd = open(redirection->file, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redirection->type == TKN_HEREDOC) // "<<"
	{
		// Handle heredoc (assumes redirection->file contains the heredoc content file path)
		fd = open(redirection->file, O_RDONLY);
		if (fd == -1)
		{
			perror("heredoc open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
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
