#include "./builtins.h"

/**This function just serves as a check if the given simple command is included
 * as one of the built-in functions or not.
 * 		Takes the command (args[0] in the t_simmcom struct) as an argument.
 * 		Returns a true/false (1/0 -bool)
*/
int is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
/* 	else if (ft_strncmp(cmd, "cd", 2) == 0)
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
		return (1); */
	else
		return (0);
}

/**This function calls the corresponding built-in functions. Cuurently only
 * echo is operational (still WIP). Haven't begun on the others yet.
 * 		Takes the field args from a t_simmcom (row on t_commtab).
 * 		Returns nothing. (??)
 */
void exec_builtin(char *args[])
{
	int	opt;
	int	i;

	if (ft_strncmp(args[0], "echo", 4) == 0)
	{
		opt = 0;
		i = 1;
		if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
		{
			opt = 1;
			i++;
		}
		echo(&args[i], opt);
	}
/* 	else if (ft_strncmp(args[0], "exit", 4) == 0)
	{
		exit_cleanup();
		free(input);
		exit(0);
	} */
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

/**This function executes the simple commands from the command table 
 * sequentially, row-by-row. A check for built-in functions is performed
 * and the corresponding function will be called appropriately (exec_prog for
 * non-built-ins). 
 * 		Takes the command table as an argument.
 * 		Returns nothing.
 */
void exec_commtab(t_commtab *table)
{
	int	i;
	t_simcomm *cmd;
	
	i = 0;
	while (i < table->count)
	{
		cmd = &table->commands[i];
		if (is_builtin(cmd->args[0]))
			exec_builtin(cmd->args);
		/* else
			exec_prog; */
		i++;
	}
	//print_commtab(table);
}