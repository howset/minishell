/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:41:13 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/17 14:35:11 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/**This function executes the simple commands from the command table
 * sequentially, row-by-row. A check for built-in functions is performed
 * and the corresponding function will be called appropriately (exec_prog for
 * non-built-ins).
 * 		Takes the command table as an argument.
 * 		Returns the exit status of the executed commands.
 */
int	exec_commtab(t_cmdtable *table, t_env **env_list, char *envp[])
{
	t_command	*cmd;
	int			exit_stat;

	exit_stat = EXIT_SUCCESS;
	cmd = table->commands;
	while (cmd)
	{
		if (cmd->type == CMD_SIMPLE)
			exit_stat = exec_simple_command(cmd, env_list, envp);
		else if (cmd->type == CMD_PIPE)
		{
			exit_stat = exec_pipe_command(cmd, env_list, envp);
			while (cmd && cmd->type == CMD_PIPE)
				cmd = cmd->next;
			continue ;
		}
		cmd = cmd->next;
	}
	return (exit_stat);
}

/*
 * exec_simple_command makes sure that builtins is executed *NOT* as a child
 * process. for non builtins, go to exec_simprog
 */
int	exec_simple_command(t_command *cmd, t_env **env_list, char *envp[])
{
	int			exit_stat;

	if (is_builtin(cmd->args[0]))
		exit_stat = exec_builtin(cmd->args, env_list, envp);
	else
		exit_stat = exec_simprog(cmd, env_list, envp);
	return (exit_stat);
}

int	exec_simprog(t_command *cmd, t_env **env_list, char *envp[])
{
	pid_t	p_id;

	p_id = fork();
	if (p_id < 0)
	{
		perror("Forking error");
		return (EXIT_FAILURE);
	}
	if (p_id == 0)
		exec_chprocess(cmd, env_list, envp);
	else
		return (wait_chprocess(p_id));
	return (EXIT_FAILURE);
}

int exec_pipe_command(t_command *cmd, t_env **env_list, char *envp[])
{
    int         status;
    pid_t       p_id;
    t_command   *current_cmd;
    int         prev_pipe[2] = {-1, -1};
    int         new_pipe[2];
    t_command   *last_cmd;

    // Find last command in pipeline
    last_cmd = cmd;
    while (last_cmd->next && last_cmd->next->type == CMD_PIPE)
        last_cmd = last_cmd->next;

    current_cmd = cmd;
    while (current_cmd && current_cmd->type == CMD_PIPE)
    {
        // If this is last command and it's a builtin
        if (current_cmd == last_cmd && is_builtin(current_cmd->args[0]))
        {
            if (prev_pipe[0] != -1)
            {
                // Setup input for builtin
                dup2(prev_pipe[0], STDIN_FILENO);
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }
            status = exec_builtin(current_cmd->args, env_list, envp);
            break;
        }

        if (current_cmd->next && pipe(new_pipe) < 0)
        {
            perror("pipe");
            return (EXIT_FAILURE);
        }

        p_id = fork();
        if (p_id < 0)
        {
            perror("Forking error");
            return (EXIT_FAILURE);
        }

        if (p_id == 0)
        {
            if (prev_pipe[0] != -1)
            {
                dup2(prev_pipe[0], STDIN_FILENO);
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }
            if (current_cmd->next)
            {
                close(new_pipe[0]);
                dup2(new_pipe[1], STDOUT_FILENO);
                close(new_pipe[1]);
            }
            exec_chprocess(current_cmd, env_list, envp);
            exit(EXIT_FAILURE);
        }

        if (prev_pipe[0] != -1)
        {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }

        if (current_cmd->next)
        {
            prev_pipe[0] = new_pipe[0];
            prev_pipe[1] = new_pipe[1];
        }

        current_cmd = current_cmd->next;
    }

    // Wait for all child processes
    while ((p_id = wait(&status)) > 0)
    {
        if (WIFEXITED(status))
            status = WEXITSTATUS(status);
    }

    return (status);
}
