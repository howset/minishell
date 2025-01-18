/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:40:12 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/18 15:15:29 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int	exec_builtin(t_command *cmd, t_env **env_list, char *envp[])
{
	int	exit_stat;
	int	stdin_backup;
	int	stdout_backup;

	// Save original file descriptors
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (cmd->redirections)
		exec_redirections(cmd->redirections);
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		exit_stat = rh_echo(cmd->args);
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		exit_stat = rh_exit(cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		exit_stat = rh_env(cmd->args, envp, env_list);
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		exit_stat = rh_export(cmd->args, env_list);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		exit_stat = rh_unset(cmd->args, env_list);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		exit_stat = rh_cd(cmd->args[1]);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		exit_stat = rh_pwd();
	else
		exit_stat = 1;
	// Restore original file descriptors
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return (exit_stat);
}

/*
 *This func is called by `exec_prog` and executed by the child process.
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

	if (cmd->args[0] && cmd->args[0][0] == '\0')
		exit(0);
	if (cmd->redirections)
		exec_redirections(cmd->redirections);
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
