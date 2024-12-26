#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H

# include "../minishell.h"
# include "../structs.h"

// Function prototypes
t_cmdtable		*create_command_table(void);
void			free_command_table(t_cmdtable *table);
t_cmdtable		*ast_to_command_table(t_ast *ast);
t_command		*create_command(char **args, t_cmd_type type);
t_redirection	*create_redirection(t_tkntype type, char *file);
void			add_command(t_cmdtable *table, t_command *cmd);
void			add_redirection(t_command *cmd, t_redirection *redir);

#endif
