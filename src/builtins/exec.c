#include "./builtins.h"
#include <sys/wait.h>

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
int exec_builtin(char *args[], t_env **env_list, char *envp[])
{
	int	opt;
	int	i;
	int	exit_stat;

	exit_stat = -1;
	if (ft_strncmp(args[0], "echo", 4) == 0)
	{
		opt = 0;
		i = 1;
		if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
		{
			opt = 1;
			i++;
		}
		exit_stat = rh_echo(&args[i], opt);
	}
	else if (ft_strncmp(args[0], "exit", 4) == 0)
	{
		printf("exit\n");
		exit_stat = rh_exit(args);
	}
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
 * 		Returns nothing.
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

char	*find_path(char *cmd, t_env *env_list)
{
	char	*path;
	char	*full_path;
	size_t	cmd_len;
	char	*start;
	char	*end;
	size_t	dir_len;
	size_t	path_len;

	while (env_list)
	{
		if (ft_strncmp(env_list->key, "PATH", 4) == 0)
		{
			path = env_list->val;
			break ;
		}
		env_list = env_list->next;
	}
	if (!path)
		return (NULL);
	cmd_len = ft_strlen(cmd);
	path_len = ft_strlen(env_list->val);
	full_path = malloc_perex(path_len, "Malloc error on full_path");
	start = path;
	end = NULL;
	while ((end = ft_strchr(start, ':')) || (*start != '\0'))
	{
		if (end)
			*end = '\0';
		dir_len = ft_strlen(start);
		if (dir_len + cmd_len + 2 > path_len)
		{
			free(full_path);
			return (NULL);
		}
		ft_strlcpy(full_path, start, path_len);
		if (full_path[dir_len - 1] != '/')
		{
			full_path[dir_len] = '/';
			ft_strlcpy(full_path + dir_len + 1, cmd, path_len - dir_len - 1);
		}
		else
			ft_strlcpy(full_path + dir_len, cmd, path_len - dir_len);
		if (access(full_path, X_OK) == 0)
		{
			if (end)
				*end = ':';
			return (full_path);
		}
		if (!end)
			break;
		start = end + 1;
	}
	free(full_path);
	return (NULL);
}

int exec_prog(char **args, t_env *env_list, char *envp[])
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	pid = fork();
	if (pid < 0)
	{
		perror("Forking error");
		return (1);
	}
	if (pid == 0)
	{
		cmd_path = find_path(args[0], env_list);
		if (!cmd_path)
		{
			ft_fprintf(STDERR_FILENO, "command not found: %s\n", args[0]);
			exit (127);
		}
		execve(cmd_path, args, envp);
		//if execve succeeds, the following will **not** be executed
		perror("Execve fails");
		free(cmd_path);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0); // Wait for the child to finish
		if (WIFEXITED(status))
			return (WEXITSTATUS(status)); // Return the child's exit status
		else
			return (1); // Return a generic error if the child didn't exit normally
	}
}
