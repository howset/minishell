/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:41:13 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 13:37:52 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	exec_simple_command(t_command *cmd, t_env **env_list, char *envp[])
{
	int	exit_stat;

	if (is_builtin(cmd->args[0]))
		exit_stat = exec_builtin(cmd, env_list, envp);
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
	return (wait_chprocess(p_id));
}

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
