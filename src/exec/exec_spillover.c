/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_spillover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:51:37 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/22 21:58:07 by hsetya           ###   ########.fr       */
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

t_command	*find_last_pipe_command(t_command *cmd)
{
	t_command	*last;

	last = cmd;
	while (last->next && last->next->type == CMD_PIPE)
		last = last->next;
	return (last);
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

int	exec_pipe_command(t_command *cmd, t_env **env_list, char *envp[])
{
	int			status;
	t_command	*current;
	t_command	*last;
	int			pipes[4];

	pipes[0] = -1;
	pipes[1] = -1;
	pipes[2] = -1;
	pipes[3] = -1;
	current = cmd;
	last = find_last_pipe_command(cmd);
	while (current && current->type == CMD_PIPE)
	{
		if (current == last && is_builtin(current->args[0]))
			return (exec_last_builtin(current, env_list, envp, &pipes[0]));
		setup_pipes(&pipes[0], &pipes[2], current->next != NULL);
		if (fork_and_handle(current, pipes, env_list, envp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		update_pipes(&pipes[0], &pipes[2], current->next != NULL);
		current = current->next;
	}
	return (wait_for_children(&status));
}
