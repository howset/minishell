/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:40:12 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 13:20:29 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

void	restore_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

int	exec_builtin(t_command *cmd, t_env **env_list, char *envp[])
{
	int	exit_stat;
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (cmd->redirections)
		exec_redirections(cmd->redirections);
	exit_stat = execute_builtin_command(cmd, env_list, envp);
	restore_fds(stdin_backup, stdout_backup);
	return (exit_stat);
}

int	execute_builtin_command(t_command *cmd, t_env **env_list, char *envp[])
{
	int	exit_stat;

	exit_stat = 1;
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		exit_stat = rh_echo(cmd->args);
	if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		exit_stat = rh_exit(cmd->args);
	if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		exit_stat = rh_env(cmd->args, envp, env_list);
	if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		exit_stat = rh_export(cmd->args, env_list);
	if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		exit_stat = rh_unset(cmd->args, env_list);
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		exit_stat = rh_cd(cmd->args[1]);
	if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		exit_stat = rh_pwd();
	return (exit_stat);
}
