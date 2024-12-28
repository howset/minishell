#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

// exec.c
int		exec_commtab(t_cmdtable *table, char *envp[]);
int		exec_builtin(char *args[], char *envp[]);
int		exec_prog(t_command *cmd, char *envp[]);
int		exec_simple_command(t_command *cmd, char *envp[]);
int		exec_pipe_command(t_command *cmd, char *envp[]);
int		is_builtin(char *cmd);

// exec_child
int		exec_chprocess(char **args, char *envp[]);
int		wait_chprocess(pid_t p_id);

// exec_pathfinding.c
char	*find_path(char *cmd);
char	*init_fullpath(size_t *path_len);
char	*process_dirs(char *path, char *cmd, char *full_path, size_t path_len);
char	*build_fullpath(char *full_path, char *dir, char *cmd, size_t path_len);

#endif
