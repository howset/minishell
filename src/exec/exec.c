/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:41:13 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 21:49:06 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/**This function executes the simple commands from the command table
 * sequentially, row-by-row. A check for built-in functions is performed
 * and the corresponding function will be called appropriately (exec_prog for
 * non-built-ins).
 * 		Takes the command table as an argument.
 * 		Returns the exit status of the executed commands.
 */
int	exec_commtab(t_cmdtable *table, t_env **env_list, char *envp[])
{
	t_command	*cmd;
	int			exit_stat;

	exit_stat = EXIT_SUCCESS;
	cmd = table->commands;
	while (cmd)
	{
		if (cmd->type == CMD_SIMPLE)
			exit_stat = exec_simple_command(cmd, env_list, envp);
		else if (cmd->type == CMD_PIPE)
		{
			exit_stat = exec_pipe_command(cmd, env_list, envp);
			while (cmd && cmd->type == CMD_PIPE)
				cmd = cmd->next;
			continue ;
		}
		cmd = cmd->next;
	}
	return (exit_stat);
}

/*
 * exec_simple_command makes sure that builtins is executed *NOT* as a child
 * process. for non builtins, go to exec_simprog
 */
int	exec_simple_command(t_command *cmd, t_env **env_list, char *envp[])
{
	int			exit_stat;

	if (is_builtin(cmd->args[0]))
		exit_stat = exec_builtin(cmd->args, env_list, envp);
	else
		exit_stat = exec_simprog(cmd, env_list, envp);
	return (exit_stat);
}

int	exec_simprog(t_command *cmd, t_env **env_list, char *envp[])
{
	pid_t	p_id;

	p_id = fork();
	if (p_id < 0)
	{
		perror("Forking error");
		return (EXIT_FAILURE);
	}
	if (p_id == 0)
		exec_chprocess(cmd, env_list, envp);
	else
		return (wait_chprocess(p_id));
	return (EXIT_FAILURE);
}

void	handle_pipe_io(t_command *cmd)
{
	if (cmd->pipe_read != -1)
	{
		dup2(cmd->pipe_read, STDIN_FILENO);
		close(cmd->pipe_read);
	}
	if (cmd->pipe_write != -1)
	{
		dup2(cmd->pipe_write, STDOUT_FILENO);
		close(cmd->pipe_write);
	}
}

void	close_pipe_fds(t_command *cmd)
{
	if (cmd->pipe_read != -1)
	{
		close(cmd->pipe_read);
	}
	if (cmd->pipe_write != -1)
	{
		close(cmd->pipe_write);
	}
}

int	fork_pipe_process(t_command *cmd, t_env **env_list, char *envp[])
{
	pid_t	p_id;

	p_id = fork();
	if (p_id < 0)
	{
		perror("Forking error");
		return (-1);
	}
	if (p_id == 0)
	{
		handle_pipe_io(cmd);
		exec_chprocess(cmd, env_list, envp);
		exit(EXIT_FAILURE);
	}
	close_pipe_fds(cmd);
	return (p_id);
}

int	exec_pipe_command(t_command *cmd, t_env **env_list, char *envp[])
{
	int			status;
	pid_t		p_id;
	t_command	*current_cmd;

	current_cmd = cmd;
	if (!cmd->next)
	{
		perror("No next command");
		return (EXIT_FAILURE);
	}
	while (current_cmd && current_cmd->type == CMD_PIPE)
	{
		p_id = fork_pipe_process(current_cmd, env_list, envp);
		if (p_id < 0)
		{
			return (EXIT_FAILURE);
		}
		status = wait_chprocess(p_id);
		if (status != EXIT_SUCCESS)
		{
			return (EXIT_FAILURE);
		}
		current_cmd = current_cmd->next;
	}
	return (status);
}
