#include "./builtins.h"

int is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	return (0);
}

void exec_builtin(char *args[])
{
	int	opt;
	int	i;
	int	arg_cnt;

	if (ft_strncmp(args[0], "echo", 4) == 0)
	{
		opt = 0;
		i = 1;
		if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
		{
			opt = 1;
			i++;
		}
		arg_cnt = 0;
		while (args[i + arg_cnt])
			arg_cnt++;
		echo(arg_cnt, &args[i], opt);
	}
}

void exec_singlecomm(t_simcomm *cmd)
{
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(cmd->args);
		return;  // Builtins don't fork
	}

	/* // Chatgpt for execvp
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (pid == 0)  // Child process
	{
		setup_redirections(cmd);  // Handle redirections

		// Execute the command
		if (execvp(cmd->args[0], cmd->args) == -1)
		{
			perror("Command execution failed");
			exit(1);
		}
	}
	else  // Parent process
	{
		if (!cmd->is_background)
			waitpid(pid, NULL, 0);  // Wait for child if not background
		else
			printf("Process running in background: PID %d\n", pid);
	} */
}

void exec_commtab(t_commtab *table)
{
	int	i;
	t_simcomm *cmd;
	
	i = 0;
	while (i < table->count)
	{
		cmd = &table->commands[i];
		if (is_builtin(cmd->args[0]))
			exec_singlecomm(cmd);
		i++;
	}
	print_commtab(table);
}