/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:40:12 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/19 13:53:35 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/**This func is called by `exec_prog` and executed by the child process.
 * `cmd_path` is the complete path to  a command by `find_path`. The execution
 *  of the command is by execve.
 * 		Takes the command (args[0]), other args, the env_list and the envp.
 * 		Returns exit status of the executed command.
 */
/*
 * // handle empty command
 * if (cmd->args[0] && cmd->args[0][0] == '\0')
 * // Apply redirections before executing the command
 * if (cmd->redirections)
 * // Add this line to exit after builtin execution
 * exit(exit_status);
 * // Check if it's a directory
 * ft_fprintf(STDERR_FILENO, "%s: command not found\n", cmd->args[0]);
 */
int	exec_chprocess(t_command *cmd, t_env **env_list, char *envp[])
{
	char	*cmd_path;
	int		exit_status;

	if (cmd->args[0] && cmd->args[0][0] == '\0')
		exit(0);
	if (cmd->redirections)
		exec_redirections(cmd->redirections);
	if (is_builtin(cmd->args[0]))
	{
		exit_status = exec_builtin(cmd, env_list, envp);
		exit(exit_status);
	}
	cmd_path = find_path(cmd->args[0], *env_list);
	if (!cmd_path)
	{
		ft_fprintf(STDERR_FILENO, "%s: command not found\n", cmd->args[0]);
		free(cmd_path);
		exit(127);
	}
	execve(cmd_path, cmd->args, envp);
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
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_fprintf(STDERR_FILENO, "Quit (core dumped)\n");
		}
		return (WTERMSIG(status) + 128);
	}
	else
		return (1);
}
