/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:44:51 by hsetya            #+#    #+#             */
/*   Updated: 2025/01/19 14:38:55 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	process_pipeline(t_command *curr, t_pipeline_data *data)
{
	int	new_pipe[2];

	while (curr && curr->type == CMD_PIPE)
	{
		if (handle_lastbuiltin(curr, data))
			break ;
		if (setup_pipe(curr->next, new_pipe) != 0)
			return (EXIT_FAILURE);
		data->status = fork_exec(curr, data, new_pipe);
		if (data->prev_pipe[0] != -1)
		{
			close(data->prev_pipe[0]);
			close(data->prev_pipe[1]);
		}
		if (curr->next)
		{
			data->prev_pipe[0] = new_pipe[0];
			data->prev_pipe[1] = new_pipe[1];
		}
		curr = curr->next;
	}
	return (data->status);
}

int	handle_lastbuiltin(t_command *curr, t_pipeline_data *data)
{
	if (curr == data->last_cmd && is_builtin(curr->args[0]))
	{
		if (data->prev_pipe[0] != -1)
		{
			dup2(data->prev_pipe[0], STDIN_FILENO);
			close(data->prev_pipe[0]);
			close(data->prev_pipe[1]);
		}
		data->status = exec_builtin(curr, data->env_list, data->envp);
		return (1);
	}
	return (0);
}

int	setup_pipe(t_command *cmd, int new_pipe[2])
{
	if (cmd && pipe(new_pipe) < 0)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	fork_exec(t_command *curr, t_pipeline_data *data, int new_pipe[2])
{
	pid_t	p_id;

	p_id = fork();
	if (p_id < 0)
	{
		perror("Forking error");
		return (EXIT_FAILURE);
	}
	if (p_id == 0)
	{
		handle_chprocess(curr, data, new_pipe);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	handle_chprocess(t_command *curr, t_pipeline_data *data,
			int new_pipe[2])
{
	if (data->prev_pipe[0] != -1)
	{
		dup2(data->prev_pipe[0], STDIN_FILENO);
		close(data->prev_pipe[0]);
		close(data->prev_pipe[1]);
	}
	if (curr->next)
	{
		close(new_pipe[0]);
		dup2(new_pipe[1], STDOUT_FILENO);
		close(new_pipe[1]);
	}
	exec_chprocess(curr, data->env_list, data->envp);
	close(STDOUT_FILENO);
}
