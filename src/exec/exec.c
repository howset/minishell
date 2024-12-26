#include "./exec.h"

/**This function just serves as a check if the given simple command is included
 * as one of the built-in functions or not.
 * 		Takes the command (args[0] in the t_simmcom struct) as an argument.
 * 		Returns a true/false (1/0 -bool)
 */
int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else
		return (0);
}

/**This function calls the corresponding built-in functions. Cuurently only
 * echo is operational (still WIP). Haven't begun on the others yet.
 * 		Takes the field args from a t_simmcom (row on t_commtab). And now also
 * 			env_list and envp for functions that required them (e.g. export).
 * 		Returns an exit status.
 */
int	exec_builtin(char *args[], t_env **env_list, char *envp[])
{
	int	exit_stat;

	if (ft_strncmp(args[0], "echo", 4) == 0)
		exit_stat = rh_echo(args);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		exit_stat = rh_exit(args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		exit_stat = rh_env(args, envp, env_list);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		exit_stat = rh_export(args, env_list);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		exit_stat = rh_unset(args, env_list);
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		exit_stat = rh_cd(args[1]);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		exit_stat = rh_pwd();
	else
		exit_stat = 1;
	return (exit_stat);
}

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
		if (is_builtin(cmd->args[0]))
			exit_stat = exec_builtin(cmd->args, env_list, envp);
		else if (cmd->type == CMD_SIMPLE)
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
		exec_chprocess(cmd->args, env_list, envp);
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
			exec_chprocess(current_cmd->args, env_list, envp);
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
