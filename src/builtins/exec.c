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
	else
		exit_stat = 1;
	return (exit_stat);
}

/*	void exec_prog(t_simcomm *cmd)
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (pid == 0) // child
	{
		setup_redirections(cmd); // deal with redirs

		// Use execve
		//if (execvp(cmd->args[0], cmd->args) == -1)
		if (execve(cmd->args[0], cmd->args) == -1)
		{
			perror("Command execution failed");
			exit(1);
		}
	}
	else  // parent
	{
		if (!cmd->is_background)
			waitpid(pid, NULL, 0);  // wqqqqqqqqait for child if not background
		else
			printf("Process running in background: PID %d\n", pid);
	} 
} */

/* t_env	*find_path(t_env *env_list, const char *key)
{
	int	i;

	i = 0;
	while (key[i])
		i++;
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, i) == 0)
		{
			printf("%s=\"%s\"\n", env_list->key, env_list->val);
			return (env_list);
		}
		env_list = env_list->next;
	}
	return (NULL);
} */

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
		/* else
			exec_prog; */
		/* else
			find_path(*env_list, "PATH"); */
		i++;
	}
	return (exit_stat);
}#include <sys/wait.h>

// Function to find the full path of the command
char *find_path(char *cmd, t_env *env_list) 
{
	char *path;
	char *path_dup;
	char *dir;
	char full_path[1024];

	while (env_list)
	{
		if (ft_strncmp(env_list->key, "PATH", 4) == 0)
			path = env_list->val;
		env_list = env_list->next;
	}
	path_dup = ft_strdup(path);
	dir = strtok(path_dup, ":");
	while (dir) 
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0) { // Check if the command is executable
			free(path_dup);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_dup);
	return NULL; // Command not found
}

int exec_prog(char **args, t_env *env_list, char *envp[]) {
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0) {
		perror("fork");
		return 1; // Return an error status
	}
	if (pid == 0) {
		// Child process
		char *cmd_path = find_path(args[0], env_list);
		if (!cmd_path) {
			fprintf(stderr, "%s: command not found\n", args[0]);
			exit(127); // Command not found exit status
		}
		execve(cmd_path, args, envp);
		// If execve fails
		perror("execve");
		free(cmd_path);
		exit(1); // Exit with error
	} else {
		// Parent process
		waitpid(pid, &status, 0); // Wait for the child to finish
		if (WIFEXITED(status))
			return WEXITSTATUS(status); // Return the child's exit status
		else
			return 1; // Return a generic error if the child didn't exit normally
	}
}
