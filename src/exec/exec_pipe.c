/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:24:18 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 13:48:29 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/* ... add header ... */

void	setup_pipe_fds(int prev_pipe[2], int new_pipe[2], int is_last)
{
	if (prev_pipe[0] != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (!is_last)
	{
		close(new_pipe[0]);
		dup2(new_pipe[1], STDOUT_FILENO);
		close(new_pipe[1]);
	}
}

void	cleanup_pipes(int prev_pipe[2], int new_pipe[2], int has_next)
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

int	handle_last_builtin(t_command *cmd, int prev_pipe[2],
						t_env **env_list, char *envp[])
{
	int	status;

	if (prev_pipe[0] != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	status = exec_builtin(cmd, env_list, envp);
	return (status);
}

int	exec_single_pipe_command(t_command *cmd, t_env **env_list, char *envp[], int prev_pipe[2], int new_pipe[2])
{
	pid_t	p_id;

	if (cmd->next && pipe(new_pipe) < 0)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	p_id = fork();
	if (p_id == 0)
	{
		setup_pipe_fds(prev_pipe, new_pipe, !cmd->next);
		exec_chprocess(cmd, env_list, envp);
	}
	return (p_id);
}

int	exec_pipe_command(t_command *cmd, t_env **env_list, char *envp[])
{
	int			status;
	t_command	*current_cmd;
	int			prev_pipe[2];
	int			new_pipe[2];

	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	current_cmd = cmd;
	while (current_cmd && current_cmd->type == CMD_PIPE)
	{
		if (exec_single_pipe_command(current_cmd, env_list, envp, prev_pipe, new_pipe) < 0)
			return (EXIT_FAILURE);
		cleanup_pipes(prev_pipe, new_pipe, current_cmd->next != NULL);
		current_cmd = current_cmd->next;
	}
	while (wait(&status) > 0)
		continue ;
	return (WEXITSTATUS(status));
}
