/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_spillover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:51:37 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/22 22:18:05 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	exec_last_builtin(t_command *cmd, t_env **env_list, char *envp[],
		int *prev_pipe)
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	return (exec_builtin(cmd, env_list, envp));
}

void	handle_child_process(t_command *cmd, int *pipes, t_env **env_list,
		char *envp[])
{
	int	*prev_pipe;
	int	*new_pipe;

	prev_pipe = &pipes[0];
	new_pipe = &pipes[2];
	if (prev_pipe[0] != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (cmd->next)
	{
		close(new_pipe[0]);
		dup2(new_pipe[1], STDOUT_FILENO);
		close(new_pipe[1]);
	}
	exec_chprocess(cmd, env_list, envp);
	exit(EXIT_FAILURE);
}

void	update_pipes(int *prev_pipe, int *new_pipe, int has_next)
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (has_next)
	{
		prev_pipe[0] = new_pipe[0];
		prev_pipe[1] = new_pipe[1];
	}
}

int	fork_and_handle(t_command *cmd, int *pipes, t_env **env_list, char *envp[])
{
	pid_t	p_id;

	p_id = fork();
	if (p_id < 0)
	{
		perror("Fork error");
		return (EXIT_FAILURE);
	}
	if (p_id == 0)
		handle_child_process(cmd, pipes, env_list, envp);
	return (EXIT_SUCCESS);
}
