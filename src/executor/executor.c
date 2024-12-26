
#include "executor.h"

void	execute_command(t_command *cmd)
{
	// This is a placeholder

	// not sure if this is the right way to handle commands

}

void	execute_command_table(t_cmdtable *table)
{

	/*
	STEPS:
	1. Check if the table is NULL
	2. Loop through the commands in the table
	3. Check for exit command
	4. Check if the command is a builtin
	5. Execute the command
	*/

	// Need env variables to move forward

	// sudo code
	/**
	 * if exit command
	 * 	exit
	 * if builtin
	 * 	execute builtin (in builtin.c) file
	 * else
	 * 	execute command
	 */
	t_command	*cmd;

	if (!table)
		return ;
	cmd = table->commands;
	while (cmd)
	{
		execute_command(cmd);
		cmd = cmd->next;
	}
}
