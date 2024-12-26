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
	int			i;
	t_command	*cmd;
	int			exit_stat;

	i = 0;
	while (i < table->cmd_count)
	{
		cmd = &table->commands[i];
		if (is_builtin(cmd->args[0]))
			exit_stat = exec_builtin(cmd->args, env_list, envp);
		else
			exit_stat = exec_prog(cmd->args, *env_list, envp);
		i++;
	}
	return (exit_stat);
}

/**Similar to `find_path`, this func is separated into a couple other funcs.
 * This func is called for non-builtins. It forks a child process that inherits
 * everything from the parent including this function. If the child process
 * executes this function, it will evaluate p_id == 0 and this func will go to
 * exec_chprocess. Whereas the parent process (p_id != 0) will wait for the
 * child process to finish (via the func wait_chprocess).
 * 		Takes the simple command row, env_list and envp.
 * 		Returns the exit status of the executed command via waitpid.
 */
int	exec_prog(char **args, t_env *env_list, char *envp[])
{
	pid_t	p_id;

	p_id = fork();
	if (p_id < 0)
	{
		perror("Forking error");
		return (EXIT_FAILURE);
	}
	if (p_id == 0)
		exec_chprocess(args, env_list, envp);
	else
		return (wait_chprocess(p_id));
	return (EXIT_FAILURE);
}
