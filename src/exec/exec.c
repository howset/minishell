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
	int			i;

	i = 0;
	while (i < table->cmd_count)
	{
		cmd = &table->commands[i];
		if (cmd->type == CMD_SIMPLE)
			exit_stat = exec_simple_command(cmd, *env_list, envp);
		else if (cmd->type == CMD_PIPE)
		{
			exit_stat = exec_pipe_command(cmd, *env_list, envp);
			while (i < table->cmd_count && table->commands[i].type == CMD_PIPE)
				i++;
		}
		i++;
	}
	return (exit_stat);
}

int	exec_simple_command(t_command *cmd, t_env *env_list, char *envp[])
{
	pid_t	p_id;
	int		is_child_process;

	p_id = fork();
	if (p_id < 0)
	{
		perror("Forking error");
		return (EXIT_FAILURE);
	}
	printf("p_id: %d\n", p_id);
	is_child_process = p_id == 0;
	if (is_child_process)
		exec_chprocess(cmd, env_list, envp);
	else
		return (wait_chprocess(p_id));
	return (EXIT_FAILURE);
}

int	exec_pipe_command(t_command *cmd, t_env *env_list, char *envp[])
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
		p_id = fork();
		if (p_id < 0)
		{
			perror("Forking error");
			return (EXIT_FAILURE);
		}
		if (p_id == 0)
		{
			if (current_cmd->pipe_read != -1)
			{
				dup2(current_cmd->pipe_read, STDIN_FILENO);
				close(current_cmd->pipe_read);
			}
			if (current_cmd->pipe_write != -1)
			{
				dup2(current_cmd->pipe_write, STDOUT_FILENO);
				close(current_cmd->pipe_write);
			}
			exec_chprocess(current_cmd, env_list, envp);
			exit(EXIT_FAILURE);
		}
		if (current_cmd->pipe_read != -1)
			close(current_cmd->pipe_read);
		if (current_cmd->pipe_write != -1)
			close(current_cmd->pipe_write);
		status = wait_chprocess(p_id);
		// If the child process failed, break the pipeline
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (WEXITSTATUS(status));
		current_cmd = current_cmd->next;
	}
	return (status);
}
