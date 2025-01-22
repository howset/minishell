/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:20:50 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 13:31:36 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/* ... add header ... */

void	handle_empty_command(t_command *cmd)
{
	if (cmd->args[0] && cmd->args[0][0] == '\0')
		exit(0);
}

void	execute_command(char *cmd_path, t_command *cmd, char *envp[])
{
	signal(SIGQUIT, SIG_DFL);
	execve(cmd_path, cmd->args, envp);
	perror("Execve fails");
	free(cmd_path);
	exit(EXIT_FAILURE);
}

int	exec_chprocess(t_command *cmd, t_env **env_list, char *envp[])
{
	char	*cmd_path;
	int		exit_status;

	handle_empty_command(cmd);
	if (cmd->redirections)
		exec_redirections(cmd->redirections);
	if (is_builtin(cmd->args[0]))
	{
		exit_status = exec_builtin(cmd, env_list, envp);
		return (exit_status);
	}
	cmd_path = find_path(cmd->args[0], *env_list);
	if (!cmd_path)
	{
		ft_fprintf(STDERR_FILENO, "%s: command not found\n", cmd->args[0]);
		free(cmd_path);
		exit(127);
	}
	execute_command(cmd_path, cmd, envp);
	return (EXIT_FAILURE);
}

void	handle_sigquit(void)
{
	ft_fprintf(STDERR_FILENO, "Quit (core dumped)\n");
}

int	wait_chprocess(pid_t p_id)
{
	int	status;

	waitpid(p_id, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			handle_sigquit();
		return (WTERMSIG(status) + 128);
	}
	return (1);
}
