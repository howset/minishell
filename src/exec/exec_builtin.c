/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:43:44 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/19 14:38:45 by hsetyamu         ###   ########.fr       */
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

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (cmd->redirections)
		exec_redirections(cmd->redirections);
	exit_stat = call_builtins(cmd, env_list, envp);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return (exit_stat);
}

int	call_builtins(t_command *cmd, t_env **env_list, char *envp[])
{
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		return (rh_echo(cmd->args));
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		return (rh_exit(cmd->args));
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		return (rh_env(cmd->args, envp, env_list));
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		return (rh_export(cmd->args, env_list));
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (rh_unset(cmd->args, env_list));
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		return (rh_cd(cmd->args[1]));
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		return (rh_pwd());
	return (1);
}
