/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:41:13 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/23 12:25:56 by reldahli         ###   ########.fr       */
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
		{
			exit_stat = exec_simple_command(cmd, env_list, envp);
			if (check_logicopnode(&cmd, exit_stat))
				continue ;
		}
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
	pid_t		p_id;

	if (is_builtin(cmd->args[0]))
		return (exec_builtin(cmd, env_list, envp));
	p_id = fork();
	if (p_id < 0)
	{
		perror("Forking error");
		return (EXIT_FAILURE);
	}
	if (p_id == 0)
		exec_chprocess(cmd, env_list, envp);
	exit_stat = wait_chprocess(p_id);
	return (exit_stat);
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

t_command	*find_last_pipe_command(t_command *cmd)
{
	t_command	*last;

	last = cmd;
	while (last->next && last->next->type == CMD_PIPE)
		last = last->next;
	return (last);
}

void	setup_pipes(int *prev_pipe, int *new_pipe, int has_next)
{
	(void)prev_pipe;
	if (has_next && pipe(new_pipe) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}
