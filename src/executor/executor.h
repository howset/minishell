
#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

void	execute_command_table(t_cmdtable *table);
int		is_builtin(char *command);
#endif
