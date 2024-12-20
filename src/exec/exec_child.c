#include "./exec.h"

/**This func is called by `exec_prog` and executed by the child process.
 * `cmd_path` is the complete path to  a command by `find_path`. The execution
 *  of the command is by execve.
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
