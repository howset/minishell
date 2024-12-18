#include "./builtins.h"
#include <sys/wait.h> //move to minishell.h(?)

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
	/* else if (ft_strncmp(args[0], "cd", 2) == 0)
		exit_stat = rh_cd(args, envp, env_list);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		exit_stat = rh_pwd(args, envp, env_list); */
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
int	exec_commtab(t_commtab *table, t_env **env_list, char *envp[])
{
	int			i;
	t_simcomm	*cmd;
	int			exit_stat;

	i = 0;
	while (i < table->count)
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

/**This function basically initializes (malloc) full_path.
 * 		Takes the env_list, and the length of the path
 * 		Returns malloc'ed full_path.
 */
char	*init_fullpath(t_env *env_list, size_t *path_len)
{
	t_env	*node;
	char	*path;
	char	*full_path;

	node = find_envvar(env_list, "PATH");
	if (!node || !node->val)
		return (NULL);
	path = node->val;
	*path_len = ft_strlen(path);
	full_path = malloc_perex(*path_len, "Malloc error on full_path");
	if (!full_path)
		return (NULL);
	return (full_path);
}

/**This function builds (puts together) the dirs leading to the command
 * 		Takes the full_path, the dir, the cmd, and the length of the path.
 * 		Returns the directories leading to the command.
 */
char	*build_fullpath(char *full_path, char *dir, char *cmd, size_t path_len)
{
	size_t	dir_len;
	size_t	cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	if (dir_len + cmd_len + 2 > path_len)
		return (NULL);
	ft_strlcpy(full_path, dir, path_len);
	if (full_path[dir_len - 1] != '/')
	{
		full_path[dir_len] = '/';
		ft_strlcpy(full_path + dir_len + 1, cmd, path_len - dir_len - 1);
	}
	else
		ft_strlcpy(full_path + dir_len, cmd, path_len - dir_len);
	return (full_path);
}

/**This function iterates over the directoriess in PATH (separated by :)and
 * tries to find the command in each of them (by means of `build_fullpath`
 * and then verification by `access`). If the command is found, it returns the
 * full path to the command.
 * 		Takes PATH, the command, the full_path and the length of the path.
 * 		Returns the full path to the command if it is found, otherwise NULL.
 */
char	*process_dirs(char *path, char *cmd, char *full_path, size_t path_len)
{
	char	*start;
	char	*end;
	char	*result;

	start = path;
	while ((end = ft_strchr(start, ':')) || (*start != '\0'))
	{
		if (end)
			*end = '\0';
		result = build_fullpath(full_path, start, cmd, path_len);
		if (result && access(full_path, X_OK) == 0)
		{
			if (end)
				*end = ':';
			return (full_path);
		}
		if (end)
			*end = ':';
		if (!end)
			break ;
		start = end + 1;
	}
	return (NULL);
}

/**This function looks now a bit weird because it is now forced to be divided
 * into several parts to meet the norm reqs, but somehow ended up a bit more
 * digestible. First, the initialization of full_path by malloc, then find
 * PATH in env_list via find_envvar and store it in path. Then `process_dirs`
 * "builds" the complete path of the cmd.
 * 		Takes a cmd (e.g. ls, or cat) and the env_list that contains PATH
 * 		Returns the complete path to the command (e.g. /dir/dir/cmd)
 */
char	*find_path(char *cmd, t_env *env_list)
{
	char	*path;
	char	*full_path;
	size_t	path_len;

	full_path = init_fullpath(env_list, &path_len);
	if (!full_path)
		return (NULL);
	path = find_envvar(env_list, "PATH")->val;
	full_path = process_dirs(path, cmd, full_path, path_len);
	if (!full_path)
		free(full_path);
	return (full_path);
}

/**This func is executed by the child process. `cmd_path` is the complete path
 * to  a command by `find_path`. The execution of the command by execve.
 * 		Takes the command (args[0]), other args, the env_list and the envp.
 * 		Returns exit status of the executed command.
 */
int	exec_chprocess(char **args, t_env *env_list, char *envp[])
{
	char	*cmd_path;

	cmd_path = find_path(args[0], env_list);
	if (!cmd_path)
	{
		ft_fprintf(STDERR_FILENO, "command not found: %s\n", args[0]);
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror("Execve fails");
	free(cmd_path);
	exit(EXIT_FAILURE);
}

/**This function is executed by the parent process. It makes the parent waits
 * until the child finished executing and takes the exit status of the child.
 * 		Takes the pid of the child process.
 * 		Returns the exit status of the child process.
 */
int	wait_chprocess(pid_t p_id)
{
	int	status;

	waitpid(p_id, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
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
