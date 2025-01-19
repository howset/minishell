/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:41:13 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/19 01:19:14 by hsetya           ###   ########.fr       */
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

int	exec_pipe_command(t_command *cmd, t_env **env_list, char *envp[])
{
	t_pipeline_data	data;

	data.last_cmd = cmd;
	while (data.last_cmd->next && data.last_cmd->next->type == CMD_PIPE)
		data.last_cmd = data.last_cmd->next;
	data.env_list = env_list;
	data.envp = envp;
	data.prev_pipe[0] = -1;
	data.prev_pipe[1] = -1;
	data.status = 0;
	data.status = process_pipeline(cmd, &data);
	data.status = waiting_pipeline(data.status);
	return (data.status);
}

int	waiting_pipeline(int status)
{
	pid_t	p_id;

	p_id = wait(&status);
	while (p_id > 0)
	{
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		p_id = wait(&status);
	}
	return (status);
}
